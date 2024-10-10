#include "Cat.h"


constexpr auto CatSize = 100.f;
constexpr auto CatSpeed = CatSize * 1;

Cat::Cat(sf::Texture Texture, sf::Vector2f Position) : movingObject(Texture, Position)
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::t_cat));
	m_char = '^';
}

Cat::~Cat()
{}

//this function moves the cat
void Cat::moveObject(sf::Time clock, std::vector<std::unique_ptr<movingObject>>& m_MovingObject)
{
	for (auto& moving : m_MovingObject)
	{
		if(moving->getChar() == '%')
		{
			sf::Vector2f location = moving->getPosition();
			float xDiff = this->getPosition().x - location.x; //diffrence in x position between cats and mouse
			float yDiff = this->getPosition().y - location.y;//diffrence in y position between cats and mouse

			bool xdiffWasNeg = false;
			bool ydiffWasNeg = false;

			if (xDiff < 0) //to check absoulute value
			{
				xDiff *= -1;
				xdiffWasNeg = true;
			}

			if (yDiff < 0) //to check absoulute value
			{
				yDiff *= -1;
				ydiffWasNeg = true;
			}

			if (xDiff < yDiff)
			{
				if (xdiffWasNeg) //if diffrence was with obsolute value
				{
					m_direction = Direction::Right;
				}
				else m_direction = Direction::Left;
			}
			else if (ydiffWasNeg)
			{
				m_direction = Direction::Down;
			}
			else m_direction = Direction::Up;


			//if mouse and cat are in the same range of x axis then goes to mouse directly
			if (xDiff < 0.8 && xDiff > -0.8)
			{
				if (getPosition().y < location.y)
				{
					m_direction = Direction::Down;
				}
				else m_direction = Direction::Up;
			}

			//if mouse and cat are in the same range of y axis then goes to mouse directly
			if (yDiff < 0.8 && yDiff > -0.8)
			{
				if (getPosition().x < location.x)
				{
					m_direction = Direction::Right;
				}
				else m_direction = Direction::Left;
			}
			

			sf::Vector2f direction = directionToVectorCat();
			m_stapSize = CatSpeed * direction * clock.asSeconds();

			m_sprite.move(m_stapSize);
		}
	}	
}

//the cats direction
sf::Vector2f Cat::directionToVectorCat()
{
	switch (m_direction)
	{
	case Direction::Up:
		return { 0, -1 };
	case Direction::Down:
		return { 0, 1 };
	case Direction::Right:
		return { 1, 0 };
	case Direction::Left:
		return { -1, 0 };
	default:
		return { 0, 0 };
	}
}

//Checks for collisions of the cat with the static objects
void Cat::checkCollition(std::vector<std::unique_ptr<movingObject>> &m_MovingObject, 
	                     std::vector<std::unique_ptr<StaticObject>> &m_StaticObject)
{
	//cheks all the static obj
	for (auto& staticc : m_StaticObject)
	{
		if (getBounds().intersects(staticc->getBounds()))
		{
			staticc->HandleCollision(*this);
		}
	}
}

//this function Handle Collision between the cat and the wall
void Cat::HandleCollision(Wall& wall)
{
	m_sprite.move(-m_stapSize);
}

//this function Handle Collision between the cat and the mouse
void Cat::HandleCollision(Mouse& mouse)
{
	m_sprite.setPosition(getOriginalPos());
	mouse.HandleCollision(*this);
}

//this function Handle Collision between the cat and the door
void Cat::HandleCollision(Door& door)
{
	m_sprite.move(-m_stapSize);
}
