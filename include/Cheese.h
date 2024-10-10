#pragma once

#include <SFML/Graphics.hpp>
#include "StaticObjects.h"
#include "Mouse.h"

class Cheese :public StaticObject
{
public:

    Cheese(sf::Texture Texture, sf::Vector2f Position);
    virtual void HandleCollision(Cheese& cheese) {};
    virtual void HandleCollision(Mouse& mouse);
    ~Cheese();

private:
};