#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <memory>
#include "Animation.hpp"
#include <unordered_map>
#include "fmod.hpp"
#include "CollisionFilters.h"
#include "Pathfinding\Pathfinder.h"
#include "TileMap\MapLoader.h"

class GameData {
public: 
	static std::shared_ptr<GameData> getInstance();

	//character info
	typedef struct{
		std::vector<std::shared_ptr<sf::Texture>> textures;//have to be kept in memory otherwise white square
		std::unordered_map<std::string, Animation> anims; //like a dictonary
		float playSpeed;
		float spriteScale;
		float maxHealth;
		float maxSpeed;
		uint16 filterCategory;
		uint16 filterMask;
		uint16 filterSensor;
	}CharInfo;
	CharInfo playerInfo;
	CharInfo aiInfo;
	CharInfo popoutInfo;

	//sounds
	FMOD::Sound * birdTweet1;
	FMOD::Sound * birdTweet2;
	FMOD::Sound * birdTweet3;
	FMOD::Sound * birdTweet4;
	FMOD::Sound * birdTweet5;
	FMOD::Sound * crowSound;
	FMOD::Sound * windAmbience;
	//textures
	sf::Texture projectileTexture;
	sf::Texture rockTexture;
	sf::Texture bushTexture;
	sf::Texture treeTexture;
	sf::Texture grassBladeTextures[6];
	sf::Texture menuPlay;
	sf::Texture menuOptions;
	sf::Texture menuQuit;
	sf::Texture menuUnfolded;
	sf::Texture menuLetters;
	sf::Texture menuBlackGradient;
	sf::Texture playSelected, optionsSelected, quitSelected;
	sf::Texture cloudTextures[3];

private:
	GameData();
	static std::weak_ptr<GameData> m_instance;
	friend std::weak_ptr <GameData>;
	friend std::shared_ptr <GameData>;
};
#endif