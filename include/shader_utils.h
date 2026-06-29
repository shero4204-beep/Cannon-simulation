#ifndef SHADER_UTILS_H_
#define SHADER_UTILS_H_

#include <GL/glew.h>
#include <string>

std::string LoadTextFile(const std::string& filename);
GLuint LoadShaders(const std::string& vertexPath, const std::string& fragmentPath);

#endif
