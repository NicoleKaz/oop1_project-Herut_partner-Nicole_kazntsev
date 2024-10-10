#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"

//abs class
class StaticObject : public GameObject
{
public:
	StaticObject();
	StaticObject(sf::Texture Texture, sf::Vector2f Position);
	virtual ~StaticObject();

private:
};
