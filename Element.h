#ifndef ELEMENT_H
#define ELEMENT_H

#pragma once
#include <SFML/Graphics.hpp>

class Element {
    public:
        Element(float x1, float x2, float y1, float y2, float z1, float z2, sf::Color color);
        bool isHit(float x, float y, float z);
        sf::Color getColor();

        float x1, x2, y1, y2, z1, z2;
        sf::Color color;
};

#endif 