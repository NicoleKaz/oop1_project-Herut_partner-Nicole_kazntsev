#include "StaticObjects.h"


StaticObject::StaticObject()
{}

StaticObject::StaticObject(sf::Texture Texture, sf::Vector2f Position) : GameObject(Texture, Position)
{}

StaticObject::~StaticObject()
{}
