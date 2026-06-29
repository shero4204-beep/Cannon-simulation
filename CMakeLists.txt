cmake_minimum_required(VERSION 3.16)
project(Assignment3_Cannon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND EXISTS "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
    set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain file")
endif()

find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(SOIL CONFIG QUIET)


set(GLEW_LINK_TARGET "")
if(TARGET GLEW::GLEW)
    set(GLEW_LINK_TARGET GLEW::GLEW)
elseif(TARGET GLEW::glew)
    set(GLEW_LINK_TARGET GLEW::glew)
elseif(TARGET unofficial::glew::glew)
    set(GLEW_LINK_TARGET unofficial::glew::glew)
else()
    message(FATAL_ERROR "GLEW target not found. Install glew:x64-windows with vcpkg.")
endif()

set(GLFW_LINK_TARGET "")
if(TARGET glfw)
    set(GLFW_LINK_TARGET glfw)
elseif(TARGET glfw3::glfw)
    set(GLFW_LINK_TARGET glfw3::glfw)
elseif(TARGET glfw3)
    set(GLFW_LINK_TARGET glfw3)
elseif(TARGET unofficial::glfw3::glfw3)
    set(GLFW_LINK_TARGET unofficial::glfw3::glfw3)
else()
    message(FATAL_ERROR "GLFW target not found. Install glfw3:x64-windows with vcpkg.")
endif()


set(SOIL_LINK_TARGET "")
if(TARGET SOIL::SOIL)
    set(SOIL_LINK_TARGET SOIL::SOIL)
elseif(TARGET soil)
    set(SOIL_LINK_TARGET soil)
elseif(TARGET unofficial::SOIL::SOIL)
    set(SOIL_LINK_TARGET unofficial::SOIL::SOIL)
else()
    find_path(SOIL_INCLUDE_DIR
        NAMES SOIL/SOIL.h
        PATH_SUFFIXES include
    )
    find_library(SOIL_LIBRARY
        NAMES SOIL soil
        PATH_SUFFIXES lib
    )

    if(NOT SOIL_INCLUDE_DIR OR NOT SOIL_LIBRARY)
        message(FATAL_ERROR "SOIL not found. Install soil:x64-windows with vcpkg.")
    endif()

    add_library(SOIL::SOIL UNKNOWN IMPORTED)
    set_target_properties(SOIL::SOIL PROPERTIES
        IMPORTED_LOCATION "${SOIL_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${SOIL_INCLUDE_DIR}"
    )
    set(SOIL_LINK_TARGET SOIL::SOIL)
endif()

add_executable(${PROJECT_NAME}
    main.cpp
    src/camera.cpp
    src/mesh.cpp
    src/shader_utils.cpp
    src/texture_utils.cpp
    src/cannon_scene.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    glm::glm
    ${GLEW_LINK_TARGET}
    ${GLFW_LINK_TARGET}
    ${SOIL_LINK_TARGET}
)

if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        _CRT_SECURE_NO_WARNINGS
        GLM_ENABLE_EXPERIMENTAL
    )
endif()
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/resource
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/resource
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)