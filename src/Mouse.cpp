#include "Mouse.h"


constexpr auto MouseSize = 400.f;
constexpr auto MouseSpeed = MouseSize * 1;

Mouse::Mouse(sf::Texture Texture, sf::Vector2f Position, const sf::Vector2f& scaleFactor) 
	: movingObject(Texture, Position)
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::t_mouse));
	m_char = '%';
	m_sprite.setScale(scaleFactor);
	m_scale = scaleFactor;
	m_keyBoard.push_back(sf::Keyboard::Up);
	m_keyBoard.push_back(sf::Keyboard::Down);
	m_keyBoard.push_back(sf::Keyboard::Left);
	m_keyBoard.push_back(sf::Keyboard::Right);
}

Mouse::~Mouse()
{}


//this function moves the mouse 
void Mouse::moveObject(sf::Time clock, std::vector<std::unique_ptr<movingObject>>& m_MovingObject)
{
	// Receive the key that was pressed
	sf::Vector2f direction = directionToVector(getKeyPress());
	// Calculate the move on the board
	m_stapSize = MouseSpeed * direction * clock.asSeconds();
	//changes the mous diraction
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
	{
		m_sprite.setScale(m_scale); 
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
	{
		m_sprite.setScale(-m_scale.x, m_scale.y);
	}	
	// Move the sprite based on the calculated step size
	m_sprite.move(m_stapSize);
}

//this function raceve which arrow key is pressed and returning it
sf::Keyboard::Key Mouse::getKeyPress() const
{
	for (int i = 0; i < m_keyBoard.size(); i++) 
	{
		if (sf::Keyboard::isKeyPressed(m_keyBoard[i]))
			return m_keyBoard[i];
	}
	return sf::Keyboard::Key();	
}

//this function is checking if the mouse can make the move 
void Mouse::checkCollition(std::vector<std::unique_ptr<movingObject>> &m_MovingObject, std::vector<std::unique_ptr<StaticObject>> &m_StaticObject)
{
	//all the static obj 
	for (auto& staticc : m_StaticObject)
	{
		if (getBounds().intersects(staticc->getBounds()))
		{
			staticc->HandleCollision(*this);
		}
	}
	//all the moving obj - the cats 
	for (auto& dynamic : m_MovingObject)
	{
		if (getBounds().intersects(dynamic->getBounds()))
		{
			dynamic->HandleCollision(*this);
		}
	}
}

//Handle collision beetwen mouse and wall
void Mouse::HandleCollision(Wall& wall)
{

	m_sprite.move(-m_stapSize);
}

//Handle collision beetwen mouse and cheese
void Mouse::HandleCollision(Cheese& cheese)
{
	//update the score
	m_score += 2;
	m_EattenCheese++;
	Resources::instance().playSound(EAT);
}

//Handle collision beetwen mouse and cat
void Mouse::HandleCollision(Cat& obj)
{
	//uptate life
	m_life--;
	m_sprite.setPosition(getOriginalPos());
	Resources::instance().playSound(MINUS_LIFE);
}

//Handle collision beetwen mouse and door
void Mouse::HandleCollision(Door& door)
{
	//Moves it back
	m_sprite.move(-m_stapSize);
}

//Handle collision beetwen mouse and key
void Mouse::HandleCollision(Key& key)
{
	//uptade score and counter
	m_score += 7;
	m_counterKey++;
	Resources::instance().playSound(KEY_SOUND);
}

//Handle collision beetwen mouse and present
void Mouse::HandleCollision(Present& present)
{
	//update score
	m_score += 5; 
	m_isDeleteCat = true;
	Resources::instance().playSound(EXTRA_LIFE);
}

//Handle collision beetwen mouse and add time present
void Mouse::HandleCollision(AddTime& addtime)
{
	//update leval time 
	m_time_collected += 10;
	m_was_clock = true;
	//update score
	m_score += 10;
	Resources::instance().playSound(CLOCK_SOUND);
}

//Handle collision beetwen mouse and add life present
void Mouse::HandleCollision(AddLife& addlife)
{
	//update score and life
	m_score += 7;
	m_life++;
	Resources::instance().playSound(EXTRA_LIFE);
}

//Handle collision beetwen mouse and add freeze present
void Mouse::HandleCollision(Freeze& freeze)
{
	//update score
	m_score += 7;
	m_isFreeze = true;
	Resources::instance().playSound(FREEZE_SOUND);
}

//Checks whether a cat should be deleted = took a freeze present
bool Mouse::getIsDeleteCat() const
{
	return m_isDeleteCat;
}

//return to false for the next cat
void Mouse::setIsDeleteCat()
{
	m_isDeleteCat = false;
}

//return to false for the next present
void Mouse::setIsFreeze()
{
	m_isFreeze = false;
}

//return m_isFreeze
bool Mouse::getIsFreeze() const
{
	return m_isFreeze;
}

//Checks if the mouse has picked up a key
bool Mouse::haveKey()
{
	if (m_counterKey > 0)
	{
		m_counterKey--;
		Resources::instance().playSound(DOOR_SOUND);
		return true;
	}
	return false;
}

//update the mouse life
void Mouse::setLife(int life)
{
	m_life = life;
}

//update the mouse life
void Mouse::setLife()
{
	m_life--;
	Resources::instance().playSound(MINUS_LIFE);
}

//update the mouse life to the start life
int Mouse::setLifeStart()
{
	m_life = 3;
	return m_life;
}

//update the mouse score
void Mouse::setScore(int score)
{
	m_score = score;
}

//get mouse life
int Mouse::getLife()
{
	return m_life;
}

//get mouse score
int Mouse::getScore()
{
	return m_score;
}

//get mouse time 
int Mouse::getTime()
{
	return m_time_collected;
}

//get mouse old time
bool Mouse::getTimeWas()
{
	bool temp = m_was_clock;
	m_was_clock = false;
	return  temp;
}

//get mouse old time
void Mouse::setTimeWas()
{
	m_was_clock = false;
}

//get mouse keys
int Mouse::getKeys()
{
	return m_counterKey;
}

//get mouse chhese counter
int Mouse::getEatten()
{
	return m_EattenCheese;
}

//set mouse cheese
void Mouse::setCheese()
{
	m_EattenCheese = 0;
}