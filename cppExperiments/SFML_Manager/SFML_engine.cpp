//
// Created by kirinokirino on 12/2/17.
//

#include "SFML_engine.h"

void SFML_engine::run() {

    loadPolygons();

    // Example shape
    sf::CircleShape circle;
    circle.setRadius(5);
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(1.0f);
    circle.setFillColor(sf::Color::Black);
    circle.setOrigin(5, 5);

    // Example sprite
    sf::Image image;
    image.loadFromFile("../test.jpeg");
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);
    sprite.setPosition(150, 150);


    while (window.isOpen()) {

        // Creates vector of triangles for drawing
        std::vector<sf::ConvexShape> triangles;
        for (int i = 0; i < polygons.size(); i++) {
            sf::ConvexShape t(3);
            t.setOutlineColor(sf::Color::White);
            t.setOutlineThickness(1.0f);
            t.setPoint(0, getPolygonPoint(i, 0));
            t.setPoint(1, getPolygonPoint(i, 1));
            t.setPoint(2, getPolygonPoint(i, 2));
            //t.setOrigin(getPolygonPoint(i, 0).x, getPolygonPoint(i, 0).y+10);
            t.move(300, 300);
            triangles.emplace_back(t);
        }

        handleEvents(window);
        window.clear();

        //polygons.back().at()
        //triangles.back().rotate(4);
        rotatePolygons(0.01f, 0.01f, 0.01f);
        // Drawing shape and sprite
        circle.setPosition(prevMouseX, prevMouseY);
        //window.draw(sprite);
        window.draw(circle);

        // Drawing each triangle
        for (auto triangle: triangles) window.draw(triangle);

        window.display();
        sf::sleep(sf::seconds(1.0f/60.0f));
    }
}

void SFML_engine::loadPolygons() {
    auto a = std::make_shared<Point>(Point(-50, -50,  0));
    auto b = std::make_shared<Point>(Point(100, 0,  50));
    auto c = std::make_shared<Point>(Point(0, 50, -50));
    // Temporary version for testing, later will be changed with command to Interpreter
    polygons.push_back(Polygon(a, b, c));
}

sf::Vector2<float> SFML_engine::rotateVector(float a, float b, float angle) {
    if (angle < 0.00001f) return sf::Vector2<float>(a, b);
    sf::Vector2<float> t;
    t.x = a*cos(angle) - b*sin(angle);
    t.y = a*sin(angle) + b*cos(angle);
    return t;
}

void SFML_engine::rotatePoint(std::shared_ptr<Point> point, float a, float b, float c) {
    Point temp(point->x(), point->y(), point->z());
    sf::Vector2<float>t(0.0f, 0.0f);

    t = rotateVector(point->x(), point->y(), a);
    temp.move(sf::Vector3<float>(-temp.x() + t.x, -temp.y() - t.y, 0));

    t = rotateVector(point->z(), point->y(), b);
    temp.move(sf::Vector3<float>(0, -temp.y() + t.y, -temp.z() + t.x));

    t = rotateVector(point->x(), point->z(), c);
    temp.move(sf::Vector3<float>( -temp.x() + t.x, 0, -temp.z() + t.y));
    point->setPosition(sf::Vector3<float>(temp.x(), temp.y(), temp.z()));
}

void SFML_engine::rotatePolygons(float x, float y, float z) {

    for (Polygon& polygon : polygons) {
        for (size_t point = 0; point < 3; point++) {
            rotatePoint(polygon.at(point), x, y, z);
        }
    }
}

void SFML_engine::handleEvents                                                                                                                                                                                                                                                                                                                                                                                                      (sf::RenderWindow &window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)             window.close();

        if (event.type == sf::Event::MouseMoved)         mouseMoved(event.mouseMove.x, event.mouseMove.y);
        if (event.type == sf::Event::MouseButtonPressed) mousePressed();
        if (event.type == sf::Event::MouseButtonReleased)mouseReleased();
        if (event.type == sf::Event::KeyPressed)         keyPressed(event.key.code);
    }
}

void SFML_engine::mouseMoved(int mouseX, int mouseY) {
    deltaMouseX = prevMouseX - mouseX;
    deltaMouseY = prevMouseY - mouseY;
    prevMouseX = mouseX;
    prevMouseY = mouseY;
}

void SFML_engine::mousePressed() {

}

void SFML_engine::mouseReleased() {

}

void SFML_engine::keyPressed(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::W) {
        //ship.setForce(sf::Vector2f(0.2, 0));
    }
    if (key == sf::Keyboard::S) {
        //ship.setForce(sf::Vector2f(-0.2f, 0));
    }
    if (key == sf::Keyboard::A) {
        //ship.setRotationForce(-0.1f);
    }
    if (key == sf::Keyboard::D) {
        //ship.setRotationForce(0.1);
    }
    if (key == sf::Keyboard::Q) {
    }
}
