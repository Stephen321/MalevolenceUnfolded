#include "AI.h"

AI::AI(sf::Vector2f position, b2World& world, std::unordered_map<std::string, Animation> anims, float playSpeed, float scale, float speed) :
Character(position, world, anims, playSpeed, scale, speed, 60, Character::collisionFilters::AI){}

void AI::update(sf::Time dt, sf::FloatRect viewBounds, sf::Vector2f playerPos){
	behaviour(playerPos);
	attackTimer += dt.asSeconds();
	Character::update(dt, viewBounds);
}

void AI::behaviour(sf::Vector2f playerPos){
	sf::Vector2f vB = playerPos - m_position;
	float angle = std::atan2(vB.y, vB.x);
	float distance = std::sqrt(vB.x * vB.x + vB.y * vB.y);
	if (distance > 25)
		m_velocity = sf::Vector2f(std::cos(angle) * SPEED, std::sin(angle) * SPEED);
	else
		m_velocity = sf::Vector2f(0, 0);
	if (target != nullptr && Debug::displayInfo)
		m_animatedSprite.setColor(sf::Color::Red);
	else if (Debug::displayInfo)
		m_animatedSprite.setColor(sf::Color::Cyan);

	if (m_attacking == false && target != nullptr && attackTimer > ATTACK_TIME){
		target->takeDamage(5);
		attackTimer = 0;
		currentAnim = &m_anims["attack"];
		m_animatedSprite.play(*currentAnim);
		m_animatedSprite.setLooped(false);
		m_attacking = true;
	}
	if (m_animatedSprite.isPlaying() == false){
		currentAnim = &m_anims["idle"];
		m_animatedSprite.play(*currentAnim);
		m_animatedSprite.setLooped(true);
		m_attacking = false;
	}
}

void AI::sensorEnd(Character*){
	target = nullptr;
}

void AI::sensorStart(Character* c){
	target = c;
}