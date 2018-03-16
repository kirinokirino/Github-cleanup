//
// Created by kirinokirino on 10/21/17.
//

#ifndef SFML_MANAGER_UTIL_H
#define SFML_MANAGER_UTIL_H
#include <math.h>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <memory>

class Point{
private:
    sf::Vector3<float> position;
public:
    Point(const sf::Vector3<float> &position) : position(position) {}
    Point(const float x, const float y, const float z) {
        position = sf::Vector3<float>(x, y, z);
    }
    void  move(const sf::Vector3<float> &position) { this->position += position; };
    void  setPosition(const sf::Vector3<float> &position) { this->position = position; };
    float x() { return position.x; };
    float y() { return position.y; };
    float z() { return position.z; };


    float at(size_t index){
        switch (index) {
            case 0: return position.x;
            case 1: return position.y;
            case 2: return position.z;
        }
    };
//    float operator[](size_t index) {
//        switch (index) {
//            case 0:
//                return position.x;
//            case 1:
//                return position.y;
//            case 2:
//                return position.z;
//        }
//    };
};

class Polygon{
private:
    std::shared_ptr<Point> first;
    std::shared_ptr<Point> second;
    std::shared_ptr<Point> third;
public:
    Polygon(std::shared_ptr<Point> first, std::shared_ptr<Point> second,
            std::shared_ptr<Point> third) : first(first), second(second), third(third) {};

    std::shared_ptr<Point> at(size_t index){
        switch (index) {
            case 0: return first;
            case 1: return second;
            case 2: return third;
        }
    };

//    std::shared_ptr<Point> operator[](size_t index) {
//        switch (index) {
//            case 0:
//                return first;
//            case 1:
//                return second;
//            case 2:
//                return third;
//        }
//    };

};

constexpr float pi();
constexpr float DegToRad();

sf::Vector2<float> rotateRadians(sf::Vector2<float> vector, float radians);
sf::Vector2<float> rotateDegrees(sf::Vector2<float> vector, float degrees);

#endif //SFML_MANAGER_UTIL_H
