#pragma once

#include <SFML/Graphics.hpp>
#include "Resources.h"

class Menu
{
public:

	Menu(int, int);

	sf::Sprite getButton(const Button) const;
	sf::Sprite getInstructions(const Instructions) const;

	void buttonRelease(const Button button);
	void buttonPress(const Button button);
	void displayRules();

private:
	//members
	const int m_WINDOW_HEIGHT;
	const int m_WINDOW_WIDTH;

	//arrays
	sf::Sprite m_Buttons[BUTTONS];
	sf::Sprite m_Instructions_Page[INSTRUCTIONS];
	void SetPosition();
};
