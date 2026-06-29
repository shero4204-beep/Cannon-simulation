#ifndef CANNON_SCENE_H_
#define CANNON_SCENE_H_

#include "mesh.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

struct CannonPart {
    Geometry geometry;
    GLuint texture = 0;
    glm::mat4 localTransform{1.0f};
    glm::vec3 materialColor{1.0f, 1.0f, 1.0f};
    bool useTexture = true;
};

struct CannonState {
    float baseYawDeg = 0.0f;
    float barrelPitchDeg = 12.0f;
    float pitchDirection = 1.0f;
};

struct RenderSettings {
    bool ambientEnabled = true;
    bool diffuseEnabled = true;
    bool specularEnabled = true;
    bool halfVectorEnabled = false;
    bool toonEnabled = false;
    bool proceduralWoodEnabled = false;
};

class CannonScene {
public:
    void Initialize(GLuint baseTexture, GLuint barrelTexture);
    void Destroy();
    void Update(float deltaTime);
    void Draw(GLuint shaderProgram,
              const glm::mat4& view,
              const glm::mat4& projection,
              const glm::vec3& cameraPosition,
              const glm::vec3& lightPosition,
              const RenderSettings& renderSettings) const;

private:
    CannonPart baseColumn_;
    CannonPart basePlate_;
    CannonPart pivotBlock_;
    CannonPart barrelOuter_;
    CannonPart barrelInner_;
    CannonState state_;

    static void AddCylinder(std::vector<Vertex>& vertices,
                            std::vector<unsigned int>& indices,
                            float radius,
                            float height,
                            int slices,
                            const glm::vec3& color,
                            float uvScaleU,
                            float uvScaleV);

    static void AddBox(std::vector<Vertex>& vertices,
                       std::vector<unsigned int>& indices,
                       const glm::vec3& halfExtents,
                       const glm::vec3& color,
                       float uvScale = 1.0f);

    void DrawPart(const CannonPart& part,
                  const glm::mat4& model,
                  GLuint shaderProgram,
                  const glm::mat4& view,
                  const glm::mat4& projection,
                  const glm::vec3& cameraPosition,
                  const glm::vec3& lightPosition,
                  const RenderSettings& renderSettings) const;
};

#endif
