//
// Created by kirinokirino on 10/21/17.
//

#include "util.h"

constexpr float pi() { return std::atan(1.0f) * 4; };

constexpr float DegToRad() { return pi() / 180.0f; };

sf::Vector2<float> rotateRadians(sf::Vector2<float> vector, float radians) {
    float ca = cos(radians);
    float sa = sin(radians);
    return sf::Vector2<float>(ca * vector.x - sa * vector.y, sa * vector.x + ca * vector.y);
}

sf::Vector2<float> rotateDegrees(sf::Vector2<float> vector, float degrees) {
    return rotateRadians(vector, degrees * DegToRad());
}

