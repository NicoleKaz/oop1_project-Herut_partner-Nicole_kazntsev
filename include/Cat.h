#pragma once

#include <SFML/Graphics.hpp>
#include "MovingObject.h"
#include "StaticObjects.h"
#include "Mouse.h"

class Cat :public movingObject
{
public:

    Cat(sf::Texture Texture, sf::Vector2f Position);
    ~Cat();
    sf::Vector2f directionToVectorCat();

    virtual void moveObject(sf::Time clock, std::vector<std::unique_ptr<movingObject>>& m_MovingObject);
    virtual void HandleCollision(Cat& obj) {};
    virtual void HandleCollision(Wall& wall);
    virtual void HandleCollision(Mouse& mouse);
    virtual void HandleCollision(Door& door);
    virtual void checkCollition(std::vector<std::unique_ptr<movingObject>>& m_MovingObject,
                                std::vector<std::unique_ptr<StaticObject>>& m_StaticObject);
private:

    std::vector<sf::Keyboard::Key> m_keyBoard;
    Direction m_direction = Stay;
};