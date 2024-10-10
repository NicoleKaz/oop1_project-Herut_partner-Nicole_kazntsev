#pragma once

#include <SFML/Graphics.hpp>
#include "MovingObject.h"
#include "StaticObjects.h"
#include "Present.h"
#include "Cat.h"

//abs class
class Mouse :public movingObject
{
public:

    Mouse(sf::Texture Texture, sf::Vector2f Position, const sf::Vector2f& scaleFactor);
    ~Mouse();
    virtual void moveObject(sf::Time clock, std::vector<std::unique_ptr<movingObject>>& m_MovingObject);
    virtual void HandleCollision(Mouse& obj) {};
    virtual void HandleCollision(Wall& wall) ;
    virtual void HandleCollision(Cheese& cheese);
    virtual void HandleCollision(Cat& obj);
    virtual void HandleCollision(Door& door) ;
    virtual void HandleCollision(Key& key);
    virtual void HandleCollision(Present& present);
    virtual void HandleCollision(AddTime& addtime);
    virtual void HandleCollision(AddLife& addlife);
    virtual void HandleCollision(Freeze& freeze);
    virtual void checkCollition(std::vector<std::unique_ptr<movingObject>>& m_MovingObject,
                                std::vector<std::unique_ptr<StaticObject>>& m_StaticObject);
    void setIsDeleteCat();
    void setIsFreeze();
    void setLife(int life);
    void setLife();
    void setScore(int score);
    void setTimeWas();
    void setCheese();
    bool getIsFreeze() const;
    bool haveKey();
    bool getIsDeleteCat() const;
    bool getTimeWas();
    int setLifeStart();
    int getLife();
    int getScore();
    int getTime();
    int getKeys();
    int getEatten();

private:
    sf::Vector2f m_scale;
    Direction m_direction = Stay;
    std::vector<sf::Keyboard::Key> m_keyBoard;
    sf::Keyboard::Key getKeyPress() const;

    int m_counterKey = 0;
    int m_life = 3;
    int m_score = 0;
    int m_EattenCheese = 0;
    int m_time_collected = 0;
    bool m_was_clock = false;
    bool m_isDeleteCat = false;
    bool m_isFreeze = false;
    bool m_inCollisionWithWall = false;
};