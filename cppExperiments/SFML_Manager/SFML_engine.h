//
// Created by kirinokirino on 12/2/17.
//

#ifndef SFML_MANAGER_SFML_ENGINE_H
#define SFML_MANAGER_SFML_ENGINE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "util.h"

class SFML_engine {
private:
    const int  WINDOW_WIDTH = 600;
    const int WINDOW_HEIGHT = 800;
    sf::RenderWindow window = sf::RenderWindow(
            sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH),
            "SFML_engine pre-alpha!");

    int prevMouseX = 0;
    int deltaMouseX = 0;
    int prevMouseY = 0;
    int deltaMouseY = 0;

    std::vector<Polygon> polygons;

public:
    sf::Vector2<float> getPolygonPoint(int whichPolygon, int whichPoint) {
        return sf::Vector2<float>(polygons.at(whichPolygon).at(whichPoint)->x(),
                                  polygons.at(whichPolygon).at(whichPoint)->y());
    }

    SFML_engine() = default;
    void run();

    void loadPolygons();
    void rotatePoint(std::shared_ptr<Point> point, float a, float b, float c);
    sf::Vector2<float> rotateVector(float a, float b, float angle);
    void rotatePolygons(float x, float y, float z);

    void handleEvents (sf::RenderWindow &window);
    void mouseMoved   (int mouseX, int mouseY);
    void mousePressed ();
    void mouseReleased();
    void keyPressed   (sf::Keyboard::Key key);
};

#endif //SFML_MANAGER_SFML_ENGINE_H
