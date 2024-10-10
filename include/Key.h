#pragma once

#include <SFML/Graphics.hpp>
#include "StaticObjects.h"
#include "Mouse.h"

class Key :public StaticObject
{
public:

    Key(sf::Texture Texture, sf::Vector2f Position);
    Key();
    ~Key();
    virtual void HandleCollision(Key& obj) {};
    virtual void HandleCollision(Mouse& mouse);

private:
};