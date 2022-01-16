#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Ship {

	static const int WIDTH = 30, HIGHT = 30;
	static const int ROWS = 2, ANIMATION_LEN = 2;

public:
	Ship();
	~Ship();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void reset();

	bool assessLanding(std::vector<sf::RectangleShape> landingPads);

	sf::Vector2f getPosition();

	float ANIMATION_DELAY = 0.2;
	float grav = 20;
	float thrust = 40;
	float rot = 100;

	sf::Vector2f velocity;
	sf::Vector2f leftLeg;
	sf::Vector2f rightLeg;

	float currentTime = 0;
	int currentCol = 0;
private:
	sf::RectangleShape ship;
	sf::Texture texture;
	sf::IntRect currentImg;

	void animate(float deltaTime);
	void setRow(int row);
};