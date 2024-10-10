#pragma once

#include <SFML/Graphics.hpp>
#include "StaticObjects.h"
#include "MovingObject.h"
#include "Mouse.h"
#include "Cat.h"


class Wall : public StaticObject
{
public:
	Wall(sf::Texture Texture, sf::Vector2f Position);
	~Wall();
	void HandleCollision(Mouse& mouse);
	void HandleCollision(Cat& cat);

private:
};