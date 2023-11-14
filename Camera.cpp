#include "Camera.h"
#include <SFML/Graphics.hpp>
#include <list>

#include "Element.h"

// Constructor
Camera::Camera(float initialX, float initialY, float initialZ, float initialPitch, float initialYaw, float screenWidth, float screenHeight)
    : x(initialX), y(initialY), z(initialZ), pitch(initialPitch), yaw(initialYaw), screenWidth(screenWidth), screenHeight(screenHeight), fastRender(true) {}


sf::Color Camera::castRay(float pixelX, float pixelY, std::vector<Element> &elements) {
    float cameraFieldOfViewX = 67.0f;
    float cameraFieldOfViewY = 90.0f;
    float maxRayCastDistance = 50.0f;

    float stepSizeFast = 1.0f;
    float stepSizeSlow = stepSizeFast / 5;

    float rayPitch = (pitch - (pixelY / screenWidth - 0.5f) * cameraFieldOfViewY) * 3.14159 / 180;
    float rayYaw = (yaw + (pixelX / screenWidth - 0.5f) * cameraFieldOfViewX) * 3.14159 / 180;

    // make 3d unit vector from camera pitch and yaw
    float rayDirX = cos(rayYaw);
    float rayDirY = sin(rayYaw);
    float rayDirZ = -cos(rayPitch);

    int* pixelColor = new int[4];

    for (float i = 0; i < maxRayCastDistance; i += fastRender ? stepSizeFast : stepSizeSlow) {

        float rayX = x + i * rayDirX;
        float rayY = y + i * rayDirY;
        float rayZ = z + i * rayDirZ;

        if (fastRender) {
            if (isHit(rayX, rayY, rayZ, elements)) {
                for (float j = i; j >= i - stepSizeFast * 2; j -= stepSizeSlow) {

                    rayX = x + j * rayDirX;
                    rayY = y + j * rayDirY;
                    rayZ = z + j * rayDirZ;

                    if (!isHit(rayX, rayY, rayZ, elements)) {
                        rayX = x + (j+stepSizeSlow) * rayDirX;
                        rayY = y + (j+stepSizeSlow)  * rayDirY;
                        rayZ = z + (j+stepSizeSlow)  * rayDirZ;

                        return getHitColor(rayX, rayY, rayZ, elements);
                    }
                }
            }
        } else {
            sf::Color color = getColorIfHit(rayX, rayY, rayZ, elements);
            if (color != sf::Color::White) {
                return color;
            }
        }

        /*
        
        */

    }
    return sf::Color::Blue;
}

sf::Color Camera::getColorIfHit(float rayX, float rayY, float rayZ, std::vector<Element> &elements) {
    if (rayZ < 0) {  
        if (int(rayX / 4) % 2 == 0) {
            if (int(rayY / 4) % 2 == 0) {
                return sf::Color(8, 156, 15, 255);
            } else {
                return sf::Color(8, 156, 15, 200);
            }
        } else {
            if (int(rayY / 4) % 2 == 0) {
                return sf::Color(8, 156, 15, 200);
            } else {
                return sf::Color(8, 156, 15, 255);
            }
        }

        return sf::Color::Green;
    } else if (rayX < 0 && rayZ > 0 && rayZ < 3) {

        if (int(rayY / 4) % 2 == 0) {
            return sf::Color(100, 100, 100, 255);
        } else {
            return sf::Color(150, 150, 150, 255);
        }

    }

    for (int i = 0; i < elements.size(); i++) {
        if (elements[i].isHit(rayX, rayY, rayZ)) {
            return elements[i].getColor();
        }
    }

    return sf::Color::White;
}

bool Camera::isHit(float rayX, float rayY, float rayZ, std::vector<Element> &elements) {
    if (rayZ < 0) {
            return true;
    } else if (rayX < 0 && rayZ > 0 && rayZ < 3) {
        return true;
    }


    // loop trought elements
    for (int i = 0; i < elements.size(); i++) {
        if (elements[i].isHit(rayX, rayY, rayZ)) {
            return true;
        }
    }

    return false;
}

sf::Color Camera::getHitColor(float rayX, float rayY, float rayZ, std::vector<Element> &elements) {
    if (rayZ < 0) {
            
        if (int(rayX / 4) % 2 == 0) {
            if (int(rayY / 4) % 2 == 0) {
                return sf::Color(8, 156, 15, 255);
            } else {
                return sf::Color(8, 156, 15, 200);
            }
        } else {
            if (int(rayY / 4) % 2 == 0) {
                return sf::Color(8, 156, 15, 200);
            } else {
                return sf::Color(8, 156, 15, 255);
            }
        }
        
        return sf::Color::Green;
    } else if (rayX < 0 && rayZ > 0 && rayZ < 3) {

        if (int(rayY / 4) % 2 == 0) {
            return sf::Color(100, 100, 100, 255);
        } else {
            return sf::Color(150, 150, 150, 255);
        }

    }

    for (int i = 0; i < elements.size(); i++) {
        if (elements[i].isHit(rayX, rayY, rayZ)) {
            return elements[i].getColor();
        }
    }

    return sf::Color::Blue;
}

// Getters
float Camera::getX() const {
    return x;
}

float Camera::getY() const {
    return y;
}

float Camera::getZ() const {
    return z;
}

float Camera::getPitch() const {
    return pitch;
}

float Camera::getYaw() const {
    return yaw;
}

// Setters
void Camera::setX(float x) {
    this->x = x;
}

void Camera::setY(float y) {
    this->y = y;
}

void Camera::setZ(float z) {
    this->z = z;
}

void Camera::setPitch(float pitch) {
    this->pitch = pitch;
}

void Camera::setYaw(float yaw) {
    this->yaw = yaw;
}
