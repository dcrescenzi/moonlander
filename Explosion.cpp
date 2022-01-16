#include "Explosion.h"
#include <iostream>

Explosion::Explosion(Ship& s) 
{
	this->explo = sf::RectangleShape(sf::Vector2f((float)SHIP_WIDTH, (float)SHIP_HIGHT));
	this->explo.setOrigin(sf::Vector2f((float)(SHIP_WIDTH / 2), (float)(SHIP_HIGHT / 2)));
	this->explo.setPosition(sf::Vector2f(s.getPosition()));

	if (!this->texture.loadFromFile("textures/explosion.png")) std::cout << "Error loading explosion texture" << std::endl;
	this->currentImg = sf::IntRect(0, 0, SHIP_WIDTH, SHIP_HIGHT);

	this->explo.setTexture(&this->texture);
	this->explo.setTextureRect(this->currentImg);
}

void Explosion::init(Ship& s)
{
	this->explo.setPosition(sf::Vector2f(s.getPosition()));
	this->currentImg = sf::IntRect(0, 0, SHIP_WIDTH, SHIP_HIGHT);
}

Explosion::~Explosion() {}

void Explosion::update(float deltaTime) 
{
	animate(deltaTime);
}

void Explosion::draw(sf::RenderWindow& window) 
{
	window.draw(this->explo);
}

void Explosion::animate(float deltaTime) 
{
	currentTime += deltaTime;

	if (currentTime >= ANIMATION_DELAY)
	{
		currentTime -= ANIMATION_DELAY;

		currentCol++;
		if ((this->currentImg.top == 0) && (currentCol >= SHIP_ANIMATION_LEN)) {
			setRow(1);
			ANIMATION_DELAY = 0.3;
		}
		if (currentCol >= SHIP_ANIMATION_LEN) currentCol = 0;

		this->currentImg.left = (currentCol * SHIP_WIDTH);
	}

	this->explo.setTextureRect(this->currentImg);
}

void Explosion::setRow(int row) 
{
	if (row != 0 && row != 1) return;

	else this->currentImg.top = SHIP_HIGHT * row;
}
