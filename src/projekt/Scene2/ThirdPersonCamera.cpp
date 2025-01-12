#include <glm/glm.hpp>

#include "ThirdPersonCamera.h"


ThirdPersonCamera::ThirdPersonCamera(float fow, float ratio, float near, float far) {
    float fowInRad = (ppgso::PI/180.0f) * fow;
    projectionMatrix = glm::perspective(fowInRad, ratio, near, far);

    cooldown = glfwGetTime();
}

void ThirdPersonCamera::update(float dt) {

    //pressing E swaps the camera positon
    if (keyboard[GLFW_KEY_E]) {
        if (glfwGetTime() - cooldown > 0.5)
        {
            cameraMode++;
            cooldown = glfwGetTime();
        }
    }

    if (cameraMode > 3)
        cameraMode = 0;

    if (cameraMode == 0) {              //default position
        position = {0.0, -10.0, -10.0};
        front = {0.0, 1.0, 1.0};
    } else if (cameraMode == 1) {       //camera is behind player and follows him left and right
        position = {0.0, -12.0, -5.0};
        front = {0.0, 2.0, 1.0};
        position.x = playerPosition.x;
    } else if (cameraMode == 2) {       //camera is above player
        position = {0.0, -2.5, -15.0};
        front = {0.0, 0.15, 1.0};
    } else if (cameraMode == 3) {       //camera is above player and rotates around him in circle
        float t = (float) glfwGetTime();
        position = {-2 * sin(t) + playerPosition.x, 3 * cos(t) - 4.5f, -12.0};
        front = {0.0, 0.15, 1.0};
        if (position.x > 4.5)
            position.x = 4.5;
        else if (position.x < -4.5)
            position.x = -4.5;
    }
    viewMatrix = lookAt(position, position + front, up);
}