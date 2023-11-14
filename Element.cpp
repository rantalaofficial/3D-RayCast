#include "Element.h"
#include <SFML/Graphics.hpp>

Element::Element(float x1, float x2, float y1, float y2, float z1, float z2, sf::Color color):
    x1(x1), x2(x2), y1(y1), y2(y2), z1(z1), z2(z2), color(color) {}

bool Element::isHit(float x, float y, float z) {
    if (x >= x1 && x <= x2 && y >= y1 && y <= y2 && z >= z1 && z <= z2) {
        return true;
    }
    return false;
}

sf::Color Element::getColor() {
    return color;
}