# Cannon-simulation
3D Cannon Simulation using OpenGL (C++), featuring real-time rendering, camera controls, textured models, and interactive lighting/shading effects. Built with GLFW, GLEW, and GLM.
This project is a 3D real-time cannon scene simulation built using C++ and OpenGL. It demonstrates modern graphics programming concepts including rendering pipelines, camera movement, lighting models, texture mapping, and shader-based visual effects.

 Features
 Real-time 3D rendering using OpenGL
 Interactive first-person camera system
 Dynamic lighting system:
Ambient lighting toggle
Diffuse lighting toggle
Specular lighting toggle
Half-vector lighting option
Advanced shading effects:
Toon shading
Procedural wood texture rendering
Texture mapping support (ground + cannon barrel)
Keyboard-controlled camera movement
Real-time scene updates and animation support
FPS-style navigation in a 3D environment
Technologies Used
C++
OpenGL
GLFW
GLEW
GLM
Controls
Camera Movement
W / A / S / D → Move forward / left / backward / right
R / F → Move up / down
Arrow Keys → Rotate camera (pitch/yaw)
Lighting & Effects
M → Toggle Ambient lighting
N → Toggle Diffuse lighting
B → Toggle Specular lighting
H → Toggle Half-vector shading
T → Toggle Toon shading
P → Toggle Procedural wood texture
System
Q / ESC → Quit application
Project Structure
/resource
    assignment3.vert   → Vertex shader
    assignment3.frag   → Fragment shader

/assets
    ottawa.png         → Ground texture
    wood.png           → Cannon barrel texture

/src
    main.cpp           → Application entry point
    camera.h           → Camera system
    cannon_scene.h     → Scene management
    shader_utils.h     → Shader loader
    texture_utils.h    → Texture loader
How It Works
Initializes GLFW window + OpenGL 3.3 core profile
Loads shaders and textures
Builds cannon scene using VAO/VBO structures
Uses a camera class for navigation
Applies real-time lighting via shader uniforms
Continuously renders frames with delta-time updates
Concepts Demonstrated
3D transformations (model/view/projection matrices)
Shader programming (vertex + fragment shaders)
Texture mapping
Lighting models (Phong shading)
Real-time input handling
Scene graph structure
Frame-based animation
👨‍💻 Author

Shreya Kashyap
