#include "Menu.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

Menu::Menu(int scWidth, int scHight) 
{
	if (!this->titleArt.loadFromFile("textures/titleArt.png")) std::cout << "Error loading title art texture" << std::endl;

	this->titleArtRect = sf::RectangleShape(sf::Vector2f(this->titleArt.getSize()));
	this->titleArtRect.setTexture(&this->titleArt);

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
		this->starVelocities.push_back(velocity);
	}
}

Menu::~Menu() {}

void Menu::update(float deltaTime, int cutoffPoint, int scHight)
{
	for (int i = 0; i < this->stars.size(); i++)
	{
		this->stars[i].move((float)(this->starVelocities[i] * deltaTime), 0.0f);

		if (this->stars[i].getPosition().x > cutoffPoint)
		{
			this->stars[i].setPosition(sf::Vector2f((float)-1 * STAR_DIM, (float)(rand() % scHight)));

		}
	}
}

void Menu::draw(sf::RenderWindow& window) 
{
	for (sf::RectangleShape star : this->stars) window.draw(star);

	window.draw(this->titleArtRect);
}