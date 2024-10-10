#include "ToolBar.h"


ToolBar::ToolBar()
{
	//set the word:
	for (int word = LIFE; word <= KEYCOUNTER; word++)
	{
		m_toolbar[word].setFont(Resources::instance().getFont());
		m_toolbar[word].setCharacterSize(30);
		m_toolbar[word].setString(m_Words[word]);
		m_toolbar[word].setFillColor(sf::Color::Green);
		m_toolbar[word].setPosition(1200.f, word * 150.f + 50);
	}
	//set the num:
	m_info_num[LIFE] = 3;
	m_info_num[SCORE] = 0;
	m_info_num[LEVEL] = 1;
	m_info_num[TIME] = 0;
	m_info_num[KEYCOUNTER] = 0;

	for (int word = LIFE; word <= KEYCOUNTER; word++)
	{
		m_Info[word].setFont(Resources::instance().getFont());
		m_Info[word].setCharacterSize(30);
		m_Info[word].setString(std::to_string(m_info_num[word]));
		m_Info[word].setFillColor(sf::Color::Green);
		m_Info[word].setPosition(1200.f, 40 + word * 150.f + 50);
	}
}

//return the string
sf::Text& ToolBar::GetText(int word)
{
	return m_toolbar[word];
}

//return the data
sf::Text& ToolBar::GetNum(int num)
{
	return m_Info[num];
}

//update the life data
void ToolBar::setLife(const int life)
{
	m_info_num[LIFE] = life;
	m_Info[LIFE].setString(std::to_string(life));
}

//update the score data
void ToolBar::SetScore(const int score)
{
	m_info_num[SCORE] = score;
	m_Info[SCORE].setString(std::to_string(score));
}

//update the leval data
void ToolBar::SetLevel(const int level)
{
	m_info_num[LEVEL] = level;
	m_Info[LEVEL].setString(std::to_string(level));
}

//update the keys data
void ToolBar::SetKeys(const int keys)
{
	m_info_num[KEYCOUNTER] = keys;
	m_Info[KEYCOUNTER].setString(std::to_string(keys));
}

//update the time data
void ToolBar::SetTime(const int time)
{
	m_info_num[TIME] = 40 - time;
	m_Info[TIME].setString(std::to_string(m_info_num[TIME]));
}

//update the life data
void ToolBar::SetTimeLeft(const int time)
{
	m_info_num[TIME] = time;
	m_Info[TIME].setString(std::to_string(m_info_num[TIME]));
}

//return the score 
int ToolBar::GetScore()
{
	return m_info_num[SCORE];
}

//return the time 
int ToolBar::GetTime()
{
	return m_info_num[TIME];
}

//return the life
int ToolBar::GetLife()
{
	return m_info_num[LIFE];
}


