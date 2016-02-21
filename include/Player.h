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
	void handleEvent(sf::Event e);
	sf::Vector2f getVelocity();
	void behaviour() override;
//protected:
private:
	typedef struct _Combo{
		std::string name;
		int frameChange;
	} Combo;
	std::vector<Character*> attackableEnemies;
	int m_joystick;
	std::queue<Combo> comboQ;
};
#endif