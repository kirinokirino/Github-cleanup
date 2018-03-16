//
// Created by kirinokirino on 10/21/17.
//

#ifndef SFML_MANAGER_OBJECT_H
#define SFML_MANAGER_OBJECT_H

#include <SFML/Graphics.hpp>
#include "util.h"

class Object : public sf::Sprite {
private:
    sf::Vector2<float> speed = {0, 0};
    sf::Vector2<float> acceleration = {0, 0};
    sf::Vector2<float> force = {0, 0};
    float rotationSpeed = 0;
    float rotationAcceleration = 0;
    float rotationForce = 0;

    sf::Texture objectTexture;

    sf::Texture &saveTexture(const std::string_view imagePath) {
        if (!objectTexture.loadFromFile(imagePath.data())) throw (666);
        this->setTexture(objectTexture);
        return objectTexture;
    }

    sf::Texture &saveTexture(const sf::Texture &texture) {
        objectTexture = texture;
        this->setTexture(objectTexture);
        return objectTexture;
    }

public:
    Object() : Sprite() {
        this->setOrigin(this->getLocalBounds().width / 2.0f, this->getLocalBounds().height / 2.0f);
    };

    Object(const std::string_view imagePath) : Sprite() {
        saveTexture(imagePath);
        this->setOrigin(this->getLocalBounds().width / 2.0f, this->getLocalBounds().height / 2.0f);
    };

    Object(const sf::Texture &texture) : Sprite() {
        saveTexture(texture);
        this->setOrigin(this->getLocalBounds().width / 2.0f, this->getLocalBounds().height / 2.0f);
    };

    Object(const sf::Sprite &sprite) : Sprite(sprite) {
        this->setOrigin(this->getLocalBounds().width / 2.0f, this->getLocalBounds().height / 2.0f);
    };

    void drawTo(sf::RenderWindow *window) { window->draw(*this); };

    void update();

    sf::Vector2<float> applyForce() {
        sf::Vector2<float> temp = force;
        force.x = 0;
        force.y = 0;
        return temp;
    }

    void setForce(sf::Vector2<float> push) {
        force += rotateDegrees(push, this->getRotation() - 90.0f);
    }

    float applyRotationForce() {
        float temp = rotationForce;
        rotationForce = 0;
        return temp;
    }

    void setRotationForce(float push) {
        rotationForce += push;
    }
};


#endif //SFML_MANAGER_OBJECT_H
