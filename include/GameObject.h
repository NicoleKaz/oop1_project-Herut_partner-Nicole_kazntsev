#pragma once

#include <SFML/Graphics.hpp>
#include "Resources.h"


class Mouse;
class Cat;
class Wall;
class StaticObject;
class movingObject;
class Door;
class Key;
class Cheese;
class Present;
class AddTime;
class AddLife;
class Freeze;

class GameObject
{
public:

	GameObject();
	GameObject (sf::Texture Texture, sf::Vector2f Position);
	void drawObject(sf::RenderWindow& m_window);
	void satScale(sf::Vector2f scale);
	const char getChar();
	const bool getIsCollide()const;

	const sf::Vector2f  getPosition();
	sf::FloatRect getBounds();
	sf::Sprite& getSprite();

    void HandleCollision(GameObject& obj);
	virtual void HandleCollision(Wall& obj) {};
	virtual void HandleCollision(Mouse& obj) {};
	virtual void HandleCollision(Cheese& obj) {};
	virtual void HandleCollision(Cat& obj) {};
	virtual void HandleCollision(Door& obj) {};
	virtual void HandleCollision(Key& obj) {};
	
protected:

	sf::Sprite m_sprite;
	char m_char;
	bool m_isCollide = false;
};