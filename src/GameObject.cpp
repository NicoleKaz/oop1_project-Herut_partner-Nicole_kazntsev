#include "GameObject.h"


GameObject::GameObject()
{
	m_char = ' ';
}

GameObject::GameObject(sf::Texture Texture, sf::Vector2f Position)
	:m_sprite(Texture)
{
	m_sprite.setPosition(Position);
	m_char = ' ';
}

//this function disply the obj
void GameObject::drawObject(sf::RenderWindow& m_window)
{
	m_window.draw(m_sprite);
}

//this function scale the obj size
void GameObject::satScale(sf::Vector2f scale)
{
	m_sprite.setScale(scale);
}

//this function return the obj place on the board
const sf::Vector2f  GameObject::getPosition()
{
	return m_sprite.getPosition();
}

//this function return the obj char
const char GameObject::getChar()
{
	return m_char;
}

//this function return the obj sprite bounds
sf::FloatRect GameObject::getBounds()
{
	return m_sprite.getGlobalBounds();
}

//this function handle with obj collision
void GameObject::HandleCollision(GameObject& obj)
{
	obj.HandleCollision(*this);
}

//this function return the obj sprite
sf::Sprite& GameObject::getSprite()
{
	return m_sprite;
}

//this function return if we need to delete any obj on the board
const bool GameObject::getIsCollide() const
{
	return m_isCollide;
}



