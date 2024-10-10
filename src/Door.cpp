#include "Door.h"


Door::Door(sf::Texture Texture, sf::Vector2f Position) : StaticObject(Texture, Position)
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::t_door));
	m_char = 'D';
}

Door::~Door()
{}

void Door::HandleCollision(Mouse& mouse)
{
	//if the mouse have a key open the door
	if (mouse.haveKey())
	{
		m_isCollide = true;
	}
	mouse.HandleCollision(*this);
}

void Door::HandleCollision(Cat& cat)
{
	cat.HandleCollision(*this);
}
