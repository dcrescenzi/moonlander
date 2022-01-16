#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Ship.h"
#include "Landscape.h"
#include "Background.h"
#include "Explosion.h"
#include "Menu.h"
#include "IntergameMenu.h"

static const int WIDTH = 800, HIGHT = 800;

int main() 
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HIGHT), "Moonlander");
	sf::Event e;

	float deltaTime = 0.0f;
	sf::Clock clock;

	bool landed = false;
	bool landingSuccessful = false;

	int gameState = 0;
	int pendingGameState = 0;

	int variation = 10;
	/*
	0 - menu
	1 - ingame
	2 - interlevel
	3 - wait

	make sure appropriate things done between switching gamestates.
	*/

	Menu menu(WIDTH, HIGHT);

	Ship ship;
	IntergameMenu intermenu(true);
	Landscape surface(350, variation, WIDTH, HIGHT);
	Explosion explosion(ship);
	Background bg(WIDTH, HIGHT);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed) window.close();
		}

		//gameloop 

		//game state logic

		if (gameState == 0)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				gameState = 1;

				variation = 10;
				surface = Landscape(350, variation, WIDTH, HIGHT);
				ship.reset();
			}
		}
		else if (gameState == 1)
		{
			if (landed)
			{
				intermenu.init(landingSuccessful);

				variation += 15;
				gameState = 2;
			}
		}
		else if (gameState == 2)
		{
			if (intermenu.doneTransiton())
			{
				if (landingSuccessful && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					gameState = 3;
					pendingGameState = 1;
					landed = false;

					surface = Landscape(350, variation, WIDTH, HIGHT);
					ship.reset();
				}
				else if (!landingSuccessful && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					gameState = 3;
					pendingGameState = 0;
					landed = false;

					surface = Landscape(350, variation, WIDTH, HIGHT);
					ship.reset();
				}
			}
		}
		else if (gameState == 3) 
		{
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) gameState = pendingGameState;
		}

		//================= 

		window.clear();

		if (gameState == 0)
		{
			menu.update(deltaTime, WIDTH, HIGHT);
			menu.draw(window);

		}
		else if (gameState == 1)
		{
			if (!landed) ship.update(deltaTime);
			if (landed && !landingSuccessful) explosion.update(deltaTime);
			bg.update(deltaTime, WIDTH, HIGHT);

			bg.draw(window);
			surface.draw(window);
			if (!landed) ship.draw(window);
			if (landed && landingSuccessful) ship.draw(window);
			else if (landed && !landingSuccessful) explosion.draw(window);

			std::vector<sf::RectangleShape> temp;
			if (((temp = surface.checkLanding(ship)).size() == 2) && !landed)
			{
				landed = true;
				landingSuccessful = ship.assessLanding(temp);

				if (!landingSuccessful) explosion.init(ship);
			}
		}
		else if (gameState == 2 && !intermenu.doneTransiton()) 
		{
			if (landed && !landingSuccessful) explosion.update(deltaTime);
			bg.update(deltaTime, WIDTH, HIGHT);

			bg.draw(window);
			surface.draw(window);
			if (!landed) ship.draw(window);
			if (landed && landingSuccessful) ship.draw(window);
			else if (landed && !landingSuccessful) explosion.draw(window);
			
			intermenu.update(deltaTime);
			intermenu.draw(window);
		}
		else if (gameState == 2) 
		{
			intermenu.update(deltaTime);
			intermenu.draw(window);
		}
	

		window.display();
	}

	return (0);
}