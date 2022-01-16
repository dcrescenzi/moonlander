#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Ship.h"

class Landscape {

	static const int NUM_BOXES = 150;

private:
	std::vector<sf::RectangleShape> landscape;
	std::vector<sf::ConvexShape> cover;

public:
	Landscape(int initHeight, int variation, int scWidth, int scHight);
	~Landscape();

	void draw(sf::RenderWindow& window);
	std::vector<sf::RectangleShape> checkLanding(Ship& ship);
	bool pointIsWithin(sf::RectangleShape bar, sf::Vector2f point);
};