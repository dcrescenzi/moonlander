#include "Background.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <time.h>

Background::Background(int scWidth, int scHight) 
{
	srand(time(NULL));

	int xPos, yPos, velocity;

	for (int i = 0; i < NUM_STARS; i++) 
	{
		sf::RectangleShape currentStar;
		xPos = rand() % scWidth;
		yPos = rand() % scHight;

		velocity = rand() % SPEED_VARIATION + 1;
		
		currentStar = sf::RectangleShape(sf::Vector2f((float)STAR_DIM, (float)STAR_DIM));
		currentStar.setPosition(sf::Vector2f((float)xPos, (float)yPos));
		currentStar.setFillColor(sf::Color::White);

		this->stars.push_back(currentStar);
		this->velocities.push_back(velocity);
	}
}

Background::~Background() {}

void Background::update(float deltaTime, int cutoffPoint, int scHight) 
{
	for (int i = 0; i < this->stars.size(); i++) 
	{
		this->stars[i].move((float)(this->velocities[i] * deltaTime), 0.0f);

		if (this->stars[i].getPosition().x > cutoffPoint) 
		{
			this->stars[i].setPosition(sf::Vector2f((float) -1 * STAR_DIM, (float)(rand() % scHight)));

		}
	}
}

void Background::draw(sf::RenderWindow& window) 
{
	for (sf::RectangleShape star : this->stars) window.draw(star);
}