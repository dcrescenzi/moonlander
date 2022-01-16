#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Background {

	static const int NUM_STARS = 20;
	static const int SPEED_VARIATION = 25;
	static const int STAR_DIM = 3;

private:
	std::vector<sf::RectangleShape> stars;
	std::vector<int> velocities;

public:
	Background(int scWidth, int scHight);
	~Background();

	void update(float deltaTime, int cutoffPoint, int scHight);
	void draw(sf::RenderWindow& window);
};