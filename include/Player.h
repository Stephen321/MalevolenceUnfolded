#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "SoundManager.h"

class Player : public Character {
public:
	Player(b2World& world, sf::Vector2f position = sf::Vector2f(1,1));
	virtual void update(sf::Time dt, sf::FloatRect viewBounds) override;
	virtual void startContact() override;
	virtual void endContact() override;
	void sensorEnd(Character*) override;
	void sensorStart(Character*) override;	
	void setEvent(sf::Event e);
	sf::Vector2f getVelocity();
//protected:
private:
	typedef struct _Combo{
		std::string name;
		int frameChange;
	} Combo;
	void behaviour();
	std::vector<Character*> attackableEnemies;
	sf::Event m_currentEvent;
	bool previousRelease = false;
	std::queue<Combo> comboQ;
};
#endif