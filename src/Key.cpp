#include "Key.h"


Key::Key(sf::Texture Texture, sf::Vector2f Position) : StaticObject(Texture, Position)
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::t_key));
	m_char = 'F';
}

Key::Key()
{}

Key::~Key()
{}

void Key::HandleCollision(Mouse& mouse)
{
	m_isCollide = true;
	mouse.HandleCollision(*this);
}
