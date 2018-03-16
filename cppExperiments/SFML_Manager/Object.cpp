//
// Created by kirinokirino on 10/21/17.
//

#include "Object.h"

void Object::update() {
    this->rotate(rotationSpeed);
    rotationSpeed += rotationAcceleration;
    rotationAcceleration = 0;
    rotationAcceleration += (applyRotationForce());

    this->move(speed);
    speed += acceleration;
    acceleration.x = 0;
    acceleration.y = 0;
    acceleration += applyForce();
}
