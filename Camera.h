#ifndef CAMERA_H
#define CAMERA_H

#pragma once
#include <SFML/Graphics.hpp>
#include "Element.h"

class Camera {
public:
    Camera(float initialX, float initialY, float initialZ, float initialPitch, float initialYaw, float screenWidth, float screenHeight);  // Constructor

    sf::Color castRay(float x, float y, std::vector<Element> &elements);

    bool isHit(float rayX, float rayY, float rayZ, std::vector<Element> &elements);
    sf::Color getHitColor(float rayX, float rayY, float rayZ, std::vector<Element> &elements);
    
    sf::Color getColorIfHit(float rayX, float rayY, float rayZ, std::vector<Element> &elements);

    // Getters
    float getX() const;
    float getY() const;
    float getZ() const;
    float getPitch() const;
    float getYaw() const;

    // Setters
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setPitch(float pitch);
    void setYaw(float yaw);

    bool fastRender;

private:
    float x;
    float y;
    float z;
    float pitch;
    float yaw;
    float screenWidth;
    float screenHeight;
};

#endif // CAMERA_H
