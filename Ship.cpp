#include "Ship.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

Ship::Ship()
{
	this->ship = sf::RectangleShape(sf::Vector2f((float)WIDTH, (float)HIGHT));
	if (!this->texture.loadFromFile("textures/ship.png")) std::cout << "Error loading ship texture" << std::endl;
	this->currentImg = sf::IntRect(0, 0, WIDTH, HIGHT);

	this->ship.setOrigin(WIDTH / 2, HIGHT / 2);

	this->ship.setTexture(&this->texture);
	this->ship.setTextureRect(this->currentImg);

	velocity.x = 0;
	velocity.y = 0;
}

Ship::~Ship() {}

void Ship::update(float deltaTime) 
{
	animate(deltaTime);
	int tempThrust = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		tempThrust = this->thrust;
		setRow(1);
	}
	else setRow(0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) this->ship.rotate(-1 * this->rot * deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) this->ship.rotate(this->rot * deltaTime);

	float rotation = this->ship.getRotation() * 3.141592f / 180;
	float fourthpi = 3.141592f / 4.5;
	float legDist = 21;

	this->leftLeg = sf::Vector2f((float)(this->ship.getPosition().x - legDist * sin(rotation + fourthpi)), (float)(this->ship.getPosition().y + legDist * cos(rotation + fourthpi)));
	this->rightLeg = sf::Vector2f((float)(this->ship.getPosition().x - legDist * sin(rotation - fourthpi)), (float)(this->ship.getPosition().y + legDist * cos(rotation - fourthpi)));

	velocity.y += deltaTime * (grav - tempThrust * cos(rotation));
	velocity.x += deltaTime * tempThrust * sin(rotation);

	this->ship.move(sf::Vector2f(velocity.x * deltaTime, velocity.y * deltaTime));
}

sf::Vector2f Ship::getPosition()
{
	return this->ship.getPosition();
}

void Ship::animate(float deltaTime) 
{
	currentTime += deltaTime;

	if (currentTime >= ANIMATION_DELAY)
	{
		currentTime -= ANIMATION_DELAY;

		currentCol++;
		if (currentCol >= ANIMATION_LEN) currentCol = 0;

		this->currentImg.left = (currentCol * WIDTH);
	}

	this->ship.setTextureRect(this->currentImg);
}

void Ship::reset() 
{
	this->ship.setPosition(sf::Vector2f(40, 40));
	this->velocity = sf::Vector2f(0, 0);
	this->ship.setRotation(0);
}

void Ship::draw(sf::RenderWindow& window) 
{
	window.draw(this->ship);
}

bool Ship::assessLanding(std::vector<sf::RectangleShape> landingPads) 
{
	float surfaceSlope = (landingPads[1].getPosition().y - landingPads[0].getPosition().y) / (landingPads[1].getPosition().x - landingPads[0].getPosition().x);

	float shipAngle = (-1 * this->ship.getRotation()) * 3.141592f / 180;
	float shipSlope = tan(shipAngle);

	float landingVelocity = sqrt(this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y);

	bool angleOK = (abs(shipSlope - surfaceSlope) <= 0.5) ? true : false;
	bool velocityOK = (landingVelocity < 30) ? true : false;

	//bool cgOK = ((this->ship.getRotation() > 315) && (this->ship.getRotation() < 45));

	return (angleOK && velocityOK);
}

void Ship::setRow(int row) 
{
	if (row != 0 && row != 1)return;

	else this->currentImg.top = HIGHT * row;
}