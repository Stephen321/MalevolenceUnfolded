#include "Popout.h"

Popout::Popout(b2World& world, Player* playerP, sf::Vector2f position, Pathfinder * pf, std::vector<Projectile>& projectiles) :
Enemy(world, CharacterType::POPOUT, playerP, position, pf),
m_popOutTimer(0),
m_inRange(false),
m_projectiles(projectiles){
	m_attackTime = 0.8f;
	m_damage = 5;
	m_visibiltyRange = 300;
	m_followPlayer = true;
	currentAnim = &m_anims["idle"];
	m_animatedSprite.play(*currentAnim);
	m_animatedSprite.setLooped(false);

	m_projectileTex = &GameData::getInstance()->projectileTexture;
} 

void Popout::burrow(){
	std::cout << "burrowing" << std::endl;
	m_followPlayer = true;
	currentAnim = &m_anims["burrow"];
	m_animatedSprite.play(*currentAnim);
	m_animatedSprite.setLooped(false);
	m_popOutTimer = -MAX_TIME;
	m_lastTargetTileCoord = sf::Vector2i();
}

void Popout::behaviour(){
	m_popOutTimer -= dt;
	if (m_followPlayer == false){
		if (m_popOutTimer <  0 && m_popOutTimer > -1.f) {
			burrow();
		}
		else if (m_inRange) {
			currentAnim = &m_anims["idle"];
			m_animatedSprite.play(*currentAnim);
			m_animatedSprite.setLooped(false);
		}
	}
	setTarget();
	getWaypoints();
	followPath();
	handleAttack();
}

void Popout::setTarget(){
	sf::Vector2f vB = player->getPosition() - getPosition();
	float distanceSquared = vB.x * vB.x + vB.y * vB.y;
	m_inRange = (distanceSquared < (m_visibiltyRange * m_visibiltyRange));
	if (m_inRange){ //player in range
		if (m_followPlayer && m_targetTileCoord != m_lastTargetTileCoord){
			m_targetTileCoord = getTileAround(player->getTileCoord());
		}
	}
	else{
		if (m_followPlayer == false){
			//burrow();
		}
		m_targetTileCoord = getTileCoord(m_startPos);
	}
}

sf::Vector2i Popout::getTileAround(const sf::Vector2i& coord){
	sf::Vector2i destCoord = getTileCoord();
	while (m_pathFinder->getWalkable(destCoord) == false ||
		   m_pathFinder->getAreaName(getTileCoord()) != m_pathFinder->getAreaName(destCoord) ||
		   getTileCoord() == destCoord){
		float angle = (rand() % 361) * DEGREES_TO_RADIANS;
		float x = player->getPosition().x + (cos(angle) * POPUP_RANGE);
		float y = player->getPosition().y + (sin(angle) * POPUP_RANGE);
		destCoord = getTileCoord(sf::Vector2f(x, y));
	}
	return destCoord;
}

void Popout::getWaypoints(){
	if (m_followPlayer && m_targetTileCoord != m_lastTargetTileCoord){ //update path
		m_waypoints.clear();
		m_waypoints.push_back(MapLoader::getPositionFromTileCoords(m_targetTileCoord.x, m_targetTileCoord.y));
		m_waypoints.push_back(getPosition());
		m_lastTargetTileCoord = m_targetTileCoord;
	}
}

void Popout::followPath(){
	if (m_waypoints.empty() == false){
		sf::Vector2f vB = m_waypoints.back() - getPosition();
		float distance = std::sqrt(vB.x * vB.x + vB.y * vB.y);

		if (distance > 5)
			m_velocity = (vB / distance) * m_speed;
		else{
			if (m_waypoints.size() == 1){
				if (m_followPlayer){
					m_followPlayer = false;
					m_animatedSprite.play(*currentAnim);
					m_animatedSprite.setLooped(true);
					m_popOutTimer = MAX_TIME;
				}
			}
			m_velocity = sf::Vector2f(0, 0);
			m_waypoints.pop_back();
		}
	}
	else{
		m_velocity = sf::Vector2f(0, 0);
	}
}

void Popout::handleAttack(){
	if (m_inRange && m_followPlayer == false && player != 0 && m_timer > m_attackTime){
		currentAnim = &m_anims["idle"];
		m_timer = 0;
		std::cout << "pop up attack" << '\n';
		m_attackTime = ((rand() / (float)RAND_MAX) / 3.f) + 0.6f;
		MAX_TIME = (rand() % 3) + 0.5f;
		m_projectiles.push_back(Projectile(sf::Sprite(*m_projectileTex), m_damage, getPosition(), player));
	}
}