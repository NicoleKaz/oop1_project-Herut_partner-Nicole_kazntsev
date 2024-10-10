#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include <memory>
#include <fstream>
#include "GameObject.h"
#include "Key.h"
#include "Door.h"
#include "Cheese.h"
#include "Wall.h"
#include "Mouse.h"
#include "Cat.h"
#include "Present.h"
#include "MovingObject.h"
#include "StaticObjects.h"


class Board
{
public:

    Board();
    bool readboard();
    bool ReadNewLevel();
    void fileReset();
    void setObjectCheese();
    void clearVector();
    void clearMatrix();
    void drawBoard(sf::RenderWindow& m_window);
    void updateGame(const sf::Time delta_Time);
    int returnMouseLife() const;
    int returnMouseLifeStart();
    int returnMouseTime() const;
    int returnMouseScore() const;
    int returnMouseKeys() const;
    int getCheese() const;
    int getEattenCheese() const;
    int getAddTime() { return m_mouse->getTime();}
    int wasAddTime() { return m_mouse->getTimeWas();}
    void setMouseData(int life, int score);
    sf::Vector2f calculateFactor();
    sf::Sprite getGameObjectMoving(const int index);

private:

    Mouse* m_mouse;
    int m_cheese = 0;
    int m_mouse_idx =0;
    int m_row = 0;
    int m_col = 0;
    bool m_isFreeze = false;
    sf::Clock m_freezeTimer;
    std::vector<std::string> m_matrixVector;
    std::ifstream m_ifile;  // the board
    std::vector<std::unique_ptr<movingObject>> m_MovingObject;
    std::vector<std::unique_ptr<StaticObject>> m_StaticObject;
};