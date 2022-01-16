#include "IntergameMenu.h"
#include <iostream>

IntergameMenu::IntergameMenu(bool playerAdvance) 
{
	this->playerAdvance = playerAdvance;
	this->doneFading = false;

	this->bg = sf::RectangleShape(sf::Vector2f((float)800, (float)800));

	if (!this->font.loadFromFile("fonts/pixelfont.ttf")) std::cout << "Error loading font file" << std::endl;

	this->outcome.setFont(this->font);
	this->message.setFont(this->font);
	this->options.setFont(this->font);

	this->outcome.setCharacterSize(60);
	this->message.setCharacterSize(20);
	this->options.setCharacterSize(20);

	this->outcome.setFillColor(sf::Color(40, 40, 40, 255));
	this->message.setFillColor(sf::Color(40, 40, 40, 255));
	this->options.setFillColor(sf::Color(40, 40, 40, 255));

	this->outcome.setPosition(sf::Vector2f(10, 0));
	this->message.setPosition(sf::Vector2f(10, 70));
	this->options.setPosition(sf::Vector2f(10, 100));

	if (playerAdvance)
	{
		this->fadeIn = sf::Color(34, 139, 34, this->alpha); //green

		this->outcome.setString("Successful Landing!");
		this->message.setString("You're out of this world!  The terrain is going to get worse...");
		this->options.setString("Press SPACE to advance");
	}
	else {
		this->fadeIn = sf::Color(136, 8, 8, this->alpha); //red

		this->outcome.setString("Landing Failed!");
		this->message.setString("Ur-anus at this game!");
		this->options.setString("Press SPACE to return to menu");
	}

	this->bg.setFillColor(this->fadeIn);
}

IntergameMenu::~IntergameMenu() 
{
	
}

void IntergameMenu::init(bool playerAdvance) 
{
	this->playerAdvance = playerAdvance;
	this->doneFading = false;
	this->alpha = 0;

	if (playerAdvance)
	{
		this->fadeIn = sf::Color(34, 139, 34, this->alpha); //green

		this->outcome.setString("Successful Landing!");
		this->message.setString("You're out of this world!  The terrain is going to get worse...");
		this->options.setString("Press SPACE to advance");
	}
	else {
		this->fadeIn = sf::Color(136, 8, 8, this->alpha); //red

		this->outcome.setString("Landing Failed!");
		this->message.setString("Ur-anus at this game!");
		this->options.setString("Press SPACE to return to menu");
	}

	this->bg.setFillColor(this->fadeIn);
}

void IntergameMenu::update(float deltaTime) 
{
	if (!this->doneFading)
	{
		currentTime += deltaTime;

		if (currentTime >= fadeDelay)
		{
			currentTime -= fadeDelay;
			alpha += 5;

			if (this->alpha >= 255)
			{
				this->alpha = 255;
				this->doneFading = true;
			}

			if (this->playerAdvance) this->fadeIn = sf::Color(34, 139, 34, this->alpha);
			else this->fadeIn = sf::Color(136, 8, 8, this->alpha);

			this->bg.setFillColor(this->fadeIn);
		}
	}
}

void IntergameMenu::draw(sf::RenderWindow& window) 
{
	window.draw(this->bg);

	window.draw(this->outcome);
	window.draw(this->message);
	window.draw(this->options);
}

bool IntergameMenu::doneTransiton()
{
	return this->doneFading;
}