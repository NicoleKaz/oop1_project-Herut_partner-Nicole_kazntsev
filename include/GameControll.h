#pragma once

#include <SFML/Graphics.hpp>
#include <Toolbar.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "Menu.h"
#include "Resources.h"
#include "Board.h"
#include "StaticObjects.h"


const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 1400;


class GameControll
{
public:

	GameControll();
	void drawMenu();
	void run();
	void instructionsLoop();
	void drawInstructions();
	void loadMusic();
	void loadBackgroundes();
	void drawToolBar();
	void updateData();
	void startGame(sf::Music& musicEnd);
	void handleClick(const sf::Vector2f&, sf::Music& music, sf::Music& musicEnd);
	void handleNextClick(const sf::Vector2f&, bool&);
	void handleMouseMoved(const sf::Vector2f, const Button, const Button);

private:

	Resources& m_resource = Resources::instance();
	Menu m_menu;
	Board m_board;
	ToolBar m_toolbar;
	sf::RenderWindow m_window;
	sf::Clock m_GameClock;
	sf::Clock m_MoveClock;
	sf::Texture m_background;
	sf::Texture m_backgroundplay;
	sf::Texture m_playerWon;
	sf::Music music;
	sf::Music musicEnd;
	int m_level = 1;
	int m_AddedTime = 0;
	bool was = false;
};
