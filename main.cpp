#include <iostream>
#include <stdexcept>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"
#include "cannon_scene.h"
#include "shader_utils.h"
#include "texture_utils.h"

namespace {
const std::string windowTitle = "COSC3307 Assignment 3 - Cannon";
const unsigned int windowWidth = 1280;
const unsigned int windowHeight = 720;
const glm::vec3 backgroundColor(0.85f, 0.88f, 0.95f);

GLFWwindow* gWindow = nullptr;
Camera gCamera;
CannonScene gScene;
RenderSettings gRenderSettings;
GLuint gShaderProgram = 0;
GLuint gBaseTexture = 0;
GLuint gBarrelTexture = 0;
float gLastFrame = 0.0f;
glm::vec3 gLightPosition(3.0f, 4.0f, 5.0f);

void PrintState(const char* name, bool value) {
    std::cout << name << ": " << (value ? "ON" : "OFF") << std::endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    (void)scancode;
    (void)mods;

    if (action != GLFW_PRESS && action != GLFW_REPEAT) {
        return;
    }

    if (key == GLFW_KEY_Q || key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
        return;
    }

    float rotFactor = 2.0f;
    float transFactor = 0.25f;

    switch (key) {
        case GLFW_KEY_UP:    gCamera.Pitch(rotFactor); break;
        case GLFW_KEY_DOWN:  gCamera.Pitch(-rotFactor); break;
        case GLFW_KEY_LEFT:  gCamera.Yaw(-rotFactor); break;
        case GLFW_KEY_RIGHT: gCamera.Yaw(rotFactor); break;
        case GLFW_KEY_W:     gCamera.MoveForward(transFactor); break;
        case GLFW_KEY_S:     gCamera.MoveBackward(transFactor); break;
        case GLFW_KEY_A:     gCamera.moveLeft(transFactor); break;
        case GLFW_KEY_D:     gCamera.MoveRight(transFactor); break;
        case GLFW_KEY_R:     gCamera.MoveUp(transFactor); break;
        case GLFW_KEY_F:     gCamera.MoveDown(transFactor); break;
        case GLFW_KEY_M:
            gRenderSettings.ambientEnabled = !gRenderSettings.ambientEnabled;
            PrintState("Ambient", gRenderSettings.ambientEnabled);
            break;
        case GLFW_KEY_N:
            gRenderSettings.diffuseEnabled = !gRenderSettings.diffuseEnabled;
            PrintState("Diffuse", gRenderSettings.diffuseEnabled);
            break;
        case GLFW_KEY_B:
            gRenderSettings.specularEnabled = !gRenderSettings.specularEnabled;
            PrintState("Specular", gRenderSettings.specularEnabled);
            break;
        case GLFW_KEY_H:
            gRenderSettings.halfVectorEnabled = !gRenderSettings.halfVectorEnabled;
            PrintState("Half Vector", gRenderSettings.halfVectorEnabled);
            break;
        case GLFW_KEY_T:
            gRenderSettings.toonEnabled = !gRenderSettings.toonEnabled;
            PrintState("Toon", gRenderSettings.toonEnabled);
            break;
        case GLFW_KEY_P:
            gRenderSettings.proceduralWoodEnabled = !gRenderSettings.proceduralWoodEnabled;
            PrintState("Procedural Wood", gRenderSettings.proceduralWoodEnabled);
            break;
        default:
            break;
    }
}

void ResizeCallback(GLFWwindow* window, int width, int height) {
    (void)window;
    if (height == 0) {
        height = 1;
    }
    glViewport(0, 0, width, height);
    gCamera.SetPerspectiveView(60.0f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
}

void Initialize() {
    gCamera.SetCamera(glm::vec3(4.0f, 3.0f, 7.0f), glm::vec3(0.0f, 1.2f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    gCamera.SetPerspectiveView(60.0f, static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 100.0f);

    gShaderProgram = LoadShaders("resource/assignment3.vert", "resource/assignment3.frag");
    gBaseTexture = LoadTexture2D("assets/ottawa.png");
    gBarrelTexture = LoadTexture2D("assets/wood.png");
    gScene.Initialize(gBaseTexture, gBarrelTexture);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);

    std::cout << "Controls\n"
              << "M : Ambient on/off\n"
              << "N : Diffuse on/off\n"
              << "B : Specular on/off\n"
              << "H : Half-vector on/off\n"
              << "T : Toon shading on/off\n"
              << "P : Procedural wood on/off\n"
              << "Arrow keys / W A S D R F : camera move\n"
              << "Q or ESC : quit\n";
}

void RenderFrame() {
    const float currentTime = static_cast<float>(glfwGetTime());
    const float deltaTime = currentTime - gLastFrame;
    gLastFrame = currentTime;

    gScene.Update(deltaTime);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view;
    glm::mat4 projection;
    view = gCamera.GetViewMatrix(&view);
    projection = gCamera.GetProjectionMatrix(&projection);

    gScene.Draw(gShaderProgram, view, projection, gCamera.GetPosition(), gLightPosition, gRenderSettings);
}

void Cleanup() {
    gScene.Destroy();
    if (gBaseTexture != 0) {
        glDeleteTextures(1, &gBaseTexture);
    }
    if (gBarrelTexture != 0) {
        glDeleteTextures(1, &gBarrelTexture);
    }
    if (gShaderProgram != 0) {
        glDeleteProgram(gShaderProgram);
    }
}
} 

int main() {
    try {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        gWindow = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr);
        if (!gWindow) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(gWindow);
        glfwSetFramebufferSizeCallback(gWindow, ResizeCallback);
        glfwSetKeyCallback(gWindow, KeyCallback);

        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (err != GLEW_OK) {
            throw std::runtime_error(std::string("GLEW init failed: ") + reinterpret_cast<const char*>(glewGetErrorString(err)));
        }

        glGetError();

        Initialize();
        ResizeCallback(gWindow, windowWidth, windowHeight);
        gLastFrame = static_cast<float>(glfwGetTime());

        while (!glfwWindowShouldClose(gWindow)) {
            RenderFrame();
            glfwSwapBuffers(gWindow);
            glfwPollEvents();
        }

        Cleanup();
        glfwDestroyWindow(gWindow);
        glfwTerminate();
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        Cleanup();
        if (gWindow != nullptr) {
            glfwDestroyWindow(gWindow);
        }
        glfwTerminate();
        return -1;
    }
}
