#ifndef MESH_H_
#define MESH_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec3 normal;
    glm::vec2 uv;
};

struct Geometry {
    GLuint vbo = 0;
    GLuint ibo = 0;
    GLuint vao = 0;
    GLsizei indexCount = 0;
};

Geometry CreateGeometry(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
void DestroyGeometry(Geometry& geometry);

#endif
