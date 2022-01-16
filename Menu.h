#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Menu {

static const int NUM_STARS = 40;
static const int SPEED_VARIATION = 25;
static const int STAR_DIM = 3;

private:
	sf::Texture titleArt;
	sf::RectangleShape titleArtRect;
	std::vector<sf::RectangleShape> stars;
	std::vector<int> starVelocities;

public:
	Menu(int scWdith, int scHight);
	~Menu();

	void update(float deltaTime, int cutoffPoint, int scHight);
	void draw(sf::RenderWindow& window);
};