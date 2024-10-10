#include "Present.h"


Present::Present(sf::Texture Texture, sf::Vector2f Position) : StaticObject(Texture, Position)
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::t_present));
	m_char = '$';
}

Present::~Present()
{}

//Handle collision between mouse and present
void Present::HandleCollision(Mouse& mouse)
{
	m_isCollide = true;
	mouse.HandleCollision(*this);
}

//-------------------------------------------------------------------------------------------------
AddTime::AddTime(sf::Texture Texture, sf::Vector2f Position) : Present(Texture, Position)
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::t_timeGift));
	m_char = 'T';
}

AddTime::~AddTime()
{}

//Handle collision between mouse and add time
void AddTime::HandleCollision(Mouse& mouse)
{
	m_isCollide = true;
	mouse.HandleCollision(*this);
}
//-------------------------------------------------------------------------------------------------
AddLife::AddLife(sf::Texture Texture, sf::Vector2f Position) : Present(Texture, Position)
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::t_lifeGift));
	m_char = 'L';
}

AddLife::~AddLife()
{}

//Handle collision between mouse and add life
void AddLife::HandleCollision(Mouse& mouse)
{
	m_isCollide = true;
	mouse.HandleCollision(*this);
}
//-------------------------------------------------------------------------------------------------
Freeze::Freeze(sf::Texture Texture, sf::Vector2f Position) : Present(Texture, Position)
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::t_freezeGift));
	m_char = 'Z';
}

Freeze::~Freeze()
{}

//Handle collision between mouse and freeze
void Freeze::HandleCollision(Mouse& mouse)
{
	m_isCollide = true;
	mouse.HandleCollision(*this);
}