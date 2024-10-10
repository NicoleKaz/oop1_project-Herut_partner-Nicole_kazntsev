#pragma once

#include <SFML/Graphics.hpp>
#include "StaticObjects.h"
#include "Mouse.h"

class Present :public StaticObject
{
public:

    Present(sf::Texture Texture, sf::Vector2f Position);
    ~Present();
    virtual void HandleCollision(Present& obj) {};
    virtual void HandleCollision(Mouse& mouse);

private:
};
//-------------------------------------------------------------------------------------------------
class AddTime :public Present
{
public:

    AddTime(sf::Texture Texture, sf::Vector2f Position);
    ~AddTime();
    virtual void HandleCollision(Mouse& mouse);

private:
};
//-------------------------------------------------------------------------------------------------
class AddLife :public Present
{
public:
    AddLife(sf::Texture Texture, sf::Vector2f Position);
    ~AddLife();
    virtual void HandleCollision(Mouse& mouse);

private:
};
//-------------------------------------------------------------------------------------------------
class Freeze :public Present
{
public:
     Freeze(sf::Texture Texture, sf::Vector2f Position);
    ~Freeze();
    virtual void HandleCollision(Mouse& mouse);

private:
};