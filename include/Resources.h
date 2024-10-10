#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>
#include <vector>

//enum
enum Instructions { GAME_RULES };
enum Button { PLAY, HELP, EXIT, VIDEO_PLAY, BACK };
enum Direction { Up, Down, Right, Left, Stay };
enum ToolBarWord { LIFE, SCORE, LEVEL, TIME, KEYCOUNTER };
enum Sound { CLICK, MINUS_LIFE, EAT, CLOCK_SOUND, DOOR_SOUND, FREEZE_SOUND, KEY_SOUND, GAME_OVER, WIN, EXTRA_LIFE};
enum Music { SONG, SECOND_END };
enum Object { MOUSE, KEY, WALL, DOOR, CHEESE, PRESENT, ADD_LIFE, FREEZE, ADD_TIME };

//consts
const int BUTTONS = 5;
const int INSTRUCTIONS = 1;
const int GAME_OBJECTS = 9;
const int TOOL_BAR = 5;
const int SOUNDS = 10;
const int MUSIC = 2;
const float SPRITE_SIZE = 400.f;


class Resources
{
public:

	enum TextureObject
	{
		t_wall, t_door, t_cat ,t_mouse, t_cheese, t_present, t_key, t_lifeGift, t_timeGift, t_freezeGift,
		// Add other...
		t_Total
	};

	~Resources();
	static Resources& instance(); //static so the resources will called once
	const sf::Texture& getTexture(TextureObject texObj) const;
	const sf::Font& getFont() const;
	sf::Texture& GetInstruction(Instructions);
	sf::Texture& GetButton(Button);
	void playSound(Sound);

private:
	Resources(); //private so there will be no duplicates
	Resources(const Resources&) = default;
	Resources& operator=(const Resources&) = default;
	void loadTextures();

	sf::Font m_font;
	sf::CircleShape player;
	sf::Sound m_sound;
	sf::Music m_music;
	sf::Texture m_ButtonTextures[BUTTONS];
	sf::Texture m_InstructionsTextures[INSTRUCTIONS];

	std::vector<sf::Texture> m_textureVec;
	std::vector<sf::Texture> m_MenuTexture;
	std::vector<sf::SoundBuffer> m_soundVector;
	std::vector<sf::Music> m_musicVector;
	std::string m_ButtonFiles[BUTTONS] = { "Play.png", "Help.png", "Exit.png" , "VideoPlay.png" , "Back.png" };
	std::string m_MusicFiles[MUSIC] = { "Song.wav","5_second_end.wav"};
	std::string m_InstructionFiles[INSTRUCTIONS] = {"GameRules.png" };
	std::string m_SoundFiles[SOUNDS] = { "Click.ogg", "MinusLife.ogg", "Eat.ogg", "ClockSound.ogg",
									"DoorSound.ogg" , "FreezeSound.ogg" ,
									 "KeySound.ogg" , "GameOver.ogg","win.ogg", "ExtraLifeSound.ogg" };
};