#include <SFML/Graphics.hpp>

class Box {
protected:
	const int WIDTH;
	const int HEIGHT;
	int x;
	int y;
public:
	Box() : WIDTH(200), HEIGHT(200){};
	Box(int width, int height) : WIDTH(width), HEIGHT(height){};
	virtual Box clone();
	virtual void layout();
	virtual void print(int a, int b, int c);
	void place(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int getWidth() { return WIDTH;  };
	int getheigh() { return HEIGHT; };
};

class Grid: public Box {
private:
	sf::Image gridImage;
	sf::Texture gridTexture;
	sf::Sprite gridSprite;
public:
	Grid() {
		gridImage = generateImage();
		gridTexture.loadFromImage(gridImage);
		gridSprite.setTexture(gridTexture);
	};
	Grid(int width, int height) : Box(width, height) {
		gridImage = generateImage();
		gridTexture.loadFromImage(gridImage);
		gridSprite.setTexture(gridTexture);
	};
	sf::Sprite getSprite() { return gridSprite; }
	sf::Image generateImage();
};

sf::Image Grid::generateImage() {
	sf::Image image;
	sf::Image background;
	background.loadFromFile("grid.bmp");
	image.create(WIDTH, HEIGHT, sf::Color::White);
	for (int i = 0; i < WIDTH; i += 10) {
		for (int j = 0; j < HEIGHT; j += 10) {
			image.copy(background, i, j);
		}
	}
	return image;
};

class CharBox : public Box {
private:
	char character;
public:
	CharBox(int x, int y, char character): Box(10, 10) {
		this->place(x, y);
		this->character = character;
	}
};

int main()
{
	Grid background;
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(background.getSprite());
		window.display();
	}

	return 0;
}
