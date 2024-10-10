#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"


class movingObject : public GameObject
{
public:

	movingObject(sf::Texture Texture, sf::Vector2f Position);
	virtual ~movingObject();
    virtual void moveObject(sf::Time clock , std::vector<std::unique_ptr<movingObject>>& m_MovingObject) = 0;
	virtual void checkCollition(std::vector<std::unique_ptr<movingObject>> &m_MovingObject,
								std::vector<std::unique_ptr<StaticObject>> &m_StaticObject) = 0;
	virtual void setCheese() {};
	virtual void setLife(int) {};
	virtual void setScore(int) {};
	virtual int getScore() { return 0; };
	virtual int getLife() { return 0; };
	virtual int setLifeStart() { return 0; };
	virtual int getTime() { return 0; };
	virtual int getKeys() { return 0; };
	virtual int getEatten() { return 0; };

	void setOriginalPos(sf::Vector2f Position);
	const sf::Vector2f getOriginalPos();

protected:
	sf::Vector2f directionToVector(sf::Keyboard::Key key);
	sf::Vector2f m_stapSize;
	sf::Vector2f m_originalPos;
	bool m_freeze = false;
};
