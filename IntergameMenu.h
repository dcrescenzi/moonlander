#pragma once
#include <SFML/Graphics.hpp>

class IntergameMenu {

private:
	bool playerAdvance;
	bool doneFading;
	float fadeDelay = 0.045f;
	float currentTime = 0;
	int alpha = 0;

	sf::Font font;
	sf::Color fadeIn;

	sf::Text outcome;
	sf::Text message;
	sf::Text options;

	sf::RectangleShape bg;

public: 
	IntergameMenu(bool playerAdvance);
	~IntergameMenu();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	void init(bool playerAdvance);

	bool doneTransiton();
};