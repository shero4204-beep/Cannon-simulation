#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera();

    int Roll(float angleDeg);
    int Pitch(float angleDeg);
    int Yaw(float angleDeg);

    glm::vec3 MoveForward(float numUnits);
    glm::vec3 MoveBackward(float numUnits);
    glm::vec3 MoveRight(float numUnits);
    glm::vec3 moveLeft(float numUnits);
    glm::vec3 MoveUp(float numUnits);
    glm::vec3 MoveDown(float numUnits);

    void ZoomIn(float zoom);
    void ZoomOut(float zoom);

    glm::vec3 GetPosition() const;
    glm::vec3 GetLookAtPoint() const;
    glm::vec3 GetSide() const;
    glm::vec3 GetForward() const;
    glm::vec3 GetUp() const;

    glm::mat4 GetViewMatrix(glm::mat4* viewMatrix = nullptr) const;
    glm::mat4 GetProjectionMatrix(glm::mat4* projMatrix = nullptr) const;

    void SetCamera(glm::vec3 position, glm::vec3 lookAtPoint, glm::vec3 upVector);
    int ChangeForwardVector(float x, float y, float z);
    int SetPerspectiveView(float fieldOfViewDeg, float aspectRatio, float nearPlane, float farPlane);

private:
    glm::mat4 viewMat_;
    glm::mat4 projMat_;
    glm::vec3 position_;
    glm::vec3 upVector_;
    glm::vec3 forwardVector_;
    glm::quat orientation_;
    float fieldOfViewDeg_;
    float aspectRatio_;
    float nearPlane_;
    float farPlane_;
};

#endif
