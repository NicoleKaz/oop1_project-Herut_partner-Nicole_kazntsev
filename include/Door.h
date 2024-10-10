#pragma once

#include <SFML/Graphics.hpp>
#include "StaticObjects.h"
#include "Mouse.h"
#include "Cat.h"

class Door :public StaticObject
{
public:

    Door(sf::Texture Texture, sf::Vector2f Position);
    ~Door();

    virtual void HandleCollision(Door& obj) {};
    virtual void HandleCollision(Mouse& mouse);
    virtual void HandleCollision(Cat& cat);

private:
};