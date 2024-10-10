#include "Resources.h"


Resources::Resources()
{
	loadTextures();
}

//loading all the textures
void Resources::loadTextures()
{
	//loading all images
	m_textureVec.resize(TextureObject::t_Total);
	m_textureVec[TextureObject::t_wall].loadFromFile("wall.png");
	m_textureVec[TextureObject::t_door].loadFromFile("door.png");
	m_textureVec[TextureObject::t_cat].loadFromFile("cat.png");
	m_textureVec[TextureObject::t_mouse].loadFromFile("mouse.png");
	m_textureVec[TextureObject::t_cheese].loadFromFile("cheese.png");
	m_textureVec[TextureObject::t_key].loadFromFile("key.png");
	m_textureVec[TextureObject::t_present].loadFromFile("present.png");
	m_textureVec[TextureObject::t_timeGift].loadFromFile("time.png");
	m_textureVec[TextureObject::t_lifeGift].loadFromFile("life.png");
	m_textureVec[TextureObject::t_freezeGift].loadFromFile("freeze.png");

	//loading all buttones
	for (int button = PLAY; button <= BACK; button++)
	{
		m_ButtonTextures[button].loadFromFile(m_ButtonFiles[button]);
		m_ButtonTextures[button].setSmooth(true);
	}

	for (int instruction = GAME_RULES; instruction <= GAME_RULES; instruction++)
	{
		m_InstructionsTextures[instruction].loadFromFile(m_InstructionFiles[instruction]);
		m_InstructionsTextures[instruction].setSmooth(true);
	}
	//loading all soundes
	for (int sound = CLICK; sound <= EXTRA_LIFE; sound++)
	{
		sf::SoundBuffer sounddd;
		sounddd.loadFromFile(m_SoundFiles[sound]);
		m_soundVector.push_back(sounddd);
	}
	m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
}

Resources::~Resources()
{}


Resources& Resources::instance()
{
	static Resources Resource;
	return Resource;
}

//return the obj texture
const sf::Texture& Resources::getTexture(TextureObject texObj) const
{
	return m_textureVec[texObj];
}

//tool bar font
const sf::Font& Resources::getFont() const
{
	return m_font;
}

//Buttones texture
sf::Texture& Resources::GetButton(Button button)
{
	return m_ButtonTextures[button];
}

//return the sound
void Resources::playSound(Sound sound)
{
	m_sound.setBuffer(m_soundVector[sound]);
	m_sound.play();
}

//return the instruction
sf::Texture& Resources::GetInstruction(Instructions instruction)
{
	return m_InstructionsTextures[instruction];
}