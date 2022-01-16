#pragma once
#include <SFML/Graphics.hpp>
#include "Ship.h"

class Explosion {

	static const int SHIP_WIDTH = 40, SHIP_HIGHT = 40;
	static const int SHIP_ROWS = 2, SHIP_ANIMATION_LEN = 6;

public:
	Explosion();
	Explosion(Ship& s);
	~Explosion();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	
	void init(Ship& s);

	float ANIMATION_DELAY = 0.12;
	float currentTime = 0;
	int currentCol = 0;

private:
	sf::RectangleShape explo;
	sf::Texture texture;
	sf::IntRect currentImg;

	void animate(float deltaTime);
	void setRow(int row);
};