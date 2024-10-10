#include "Menu.h"


//This functiones define the arrays
Menu::Menu(int width, int height)
	:m_WINDOW_WIDTH(width), m_WINDOW_HEIGHT(height)
{
	//the menu buttunes
	for (int button = PLAY; button <= BACK; button++)
	{
		m_Buttons[button].setTexture(Resources::instance().GetButton((Button)button));
	}
	//the instruction page 
	for (int instruction = GAME_RULES; instruction <= GAME_RULES; instruction++)
	{
		m_Instructions_Page[instruction].setTexture(Resources::instance().GetInstruction((Instructions)instruction));
	}
	m_Instructions_Page[GAME_RULES].setColor(sf::Color::Color(255, 255, 255, 0));
	SetPosition();
}

//this function showes the instructions page after the press
void Menu::displayRules()
{
	m_Instructions_Page[GAME_RULES].setColor(sf::Color::Color(255, 255, 255, 255));
}

//this function set the position 
void Menu::SetPosition()
{
	//resize Buttons 
	m_Buttons[PLAY].scale(sf::Vector2f(m_WINDOW_WIDTH * 0.195 / m_Buttons[PLAY].getTextureRect().width,
		m_WINDOW_WIDTH * 0.195 / m_Buttons[PLAY].getTextureRect().width));

	m_Buttons[HELP].scale(sf::Vector2f(m_WINDOW_WIDTH * 0.195 / m_Buttons[HELP].getTextureRect().width,
		m_WINDOW_WIDTH * 0.195 / m_Buttons[HELP].getTextureRect().width));

	m_Buttons[EXIT].scale(sf::Vector2f(m_WINDOW_WIDTH * 0.195 / m_Buttons[EXIT].getTextureRect().width,
		m_WINDOW_WIDTH * 0.195 / m_Buttons[EXIT].getTextureRect().width));

	m_Buttons[BACK].scale(sf::Vector2f(m_WINDOW_WIDTH * 0.12 / m_Buttons[BACK].getTextureRect().width,
		m_WINDOW_WIDTH * 0.12 / m_Buttons[BACK].getTextureRect().width));

	m_Buttons[VIDEO_PLAY].scale(sf::Vector2f(m_WINDOW_WIDTH * 0.12 / m_Buttons[VIDEO_PLAY].getTextureRect().width,
		m_WINDOW_WIDTH * 0.12 / m_Buttons[VIDEO_PLAY].getTextureRect().width));

	//resize Instructions:	
	m_Instructions_Page[GAME_RULES].scale(sf::Vector2f(2.4f, 1.3f));

	//locate menu:
	m_Buttons[PLAY].setPosition(sf::Vector2f((m_WINDOW_WIDTH - m_Buttons[PLAY].getTextureRect().width) * 0.5,
		m_WINDOW_HEIGHT - m_Buttons[PLAY].getTextureRect().height * 1.5 * 3));

	m_Buttons[HELP].setPosition(sf::Vector2f((m_WINDOW_WIDTH - m_Buttons[HELP].getTextureRect().width) * 0.5,
		m_WINDOW_HEIGHT - m_Buttons[HELP].getTextureRect().height * 1.5 * 2));

	m_Buttons[EXIT].setPosition(sf::Vector2f((m_WINDOW_WIDTH - m_Buttons[EXIT].getTextureRect().width) * 0.5,
		m_WINDOW_HEIGHT - m_Buttons[EXIT].getTextureRect().height * 1.5 * 1));

	m_Buttons[VIDEO_PLAY].setPosition(sf::Vector2f(m_WINDOW_WIDTH * 0.88, m_WINDOW_HEIGHT * 0.73));

	m_Buttons[BACK].setPosition(sf::Vector2f(m_WINDOW_WIDTH * 0.85, m_WINDOW_HEIGHT * 0.85));

	//locate Instructions:
	m_Instructions_Page[GAME_RULES].setPosition(sf::Vector2f(m_WINDOW_WIDTH * 0.0, m_WINDOW_HEIGHT * 0.0));
}

//Returns the button from the array
sf::Sprite Menu::getButton(const Button object) const
{
	return m_Buttons[object];
}

//make the shawow on the butten
void Menu::buttonRelease(const Button button)
{
	m_Buttons[button].setColor(sf::Color::Color(255, 255, 255));
}

//make the shawow on the butten
void Menu::buttonPress(const Button button)
{
	m_Buttons[button].setColor(sf::Color::Color(255, 255, 255, 150));
}

//Returns the from the array
sf::Sprite Menu::getInstructions(const Instructions object) const
{
	return m_Instructions_Page[object];
}
