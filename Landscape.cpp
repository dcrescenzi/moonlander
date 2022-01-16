#include "Landscape.h"
#include <stdlib.h>
#include <time.h>

Landscape::Landscape(int initHeight, int variation, int scWidth, int scHight) 
{
	srand(time(NULL));

	int prevHight = initHeight;
	int boxWidth = scWidth / NUM_BOXES + 1;
	int flatCounter = 0, tempVariation = variation;

	for (int i = 0; i < NUM_BOXES; i++) 
	{
		tempVariation = variation;

		if (flatCounter >= NUM_BOXES / 4) tempVariation = variation/10 + 1;
		if (flatCounter >= (NUM_BOXES / 4) + (NUM_BOXES / 15)) flatCounter = 0;

		int currentHight = prevHight + ((rand() % tempVariation) - (tempVariation / 2));
		sf::RectangleShape currentBox;
		sf::ConvexShape currentCover;
		
		currentBox = sf::RectangleShape(sf::Vector2f((float)boxWidth, (float)currentHight));
		currentBox.setPosition(sf::Vector2f(i * boxWidth, scHight - currentHight));

		currentCover.setPointCount(4);
		currentCover.setPoint(0, sf::Vector2f((float)((i * boxWidth) - boxWidth/2), (float)(scHight - prevHight)));
		currentCover.setPoint(1, sf::Vector2f((float)((i * boxWidth) + boxWidth/2), (float)(scHight - currentHight)));
		currentCover.setPoint(2, sf::Vector2f((float)((i * boxWidth) + boxWidth/2), (float)scHight));
		currentCover.setPoint(3, sf::Vector2f((float)((i * boxWidth) - boxWidth/2), (float)scHight));

		currentCover.setFillColor(sf::Color(112, 128, 144, 255));

		this->cover.push_back(currentCover);
		this->landscape.push_back(currentBox);

		prevHight = currentHight;
		flatCounter++;
	}

	sf::ConvexShape fin;
	fin.setPointCount(4);
	fin.setPoint(0, sf::Vector2f((float)((NUM_BOXES * boxWidth) - boxWidth), (float)(scHight - prevHight)));
	fin.setPoint(1, sf::Vector2f((float)(NUM_BOXES * boxWidth), (float)(scHight - prevHight)));
	fin.setPoint(2, sf::Vector2f((float)(NUM_BOXES * boxWidth), (float)scHight));
	fin.setPoint(3, sf::Vector2f((float)((NUM_BOXES * boxWidth) - boxWidth), (float)scHight));
	fin.setFillColor(sf::Color(112, 128, 144, 255));
	this->cover.push_back(fin);
}

Landscape::~Landscape() {}

void Landscape::draw(sf::RenderWindow& window) 
{
	for (sf::ConvexShape cover : this->cover) window.draw(cover);
}

std::vector<sf::RectangleShape> Landscape::checkLanding(Ship& ship)
{
	std::vector<sf::RectangleShape> ret;

	for (int i = 0; i < this->landscape.size(); i++) 
	{
		if (pointIsWithin(this->landscape[i], ship.leftLeg)) ret.push_back(this->landscape[i]);
		if (pointIsWithin(this->landscape[i], ship.rightLeg)) ret.push_back(this->landscape[i]);
		

		if (ret.size() == 2) break;
	}

	return ret;
}

bool Landscape::pointIsWithin(sf::RectangleShape bar, sf::Vector2f point) 
{
	if ((point.x > bar.getPosition().x) && (point.x < bar.getPosition().x + bar.getSize().x)) 
	{
		if (point.y > bar.getPosition().y)
		{
			return true;
		}
	}

	return false;
}