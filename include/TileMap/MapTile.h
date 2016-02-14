#ifndef MAP_TILE_H
#define MAP_TILE_H

#include "Properties.h"
#include "SFML\Graphics.hpp"

class MapTile : public sf::Drawable {
public:

	MapTile(sf::Sprite sprite, int gid, int width, int height, PropertyMap* properties = 0, int layer = 0);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void getPropertyString(const std::string& name, const std::string& value);
	std::string getPropertyString(const std::string& name);

private:
	sf::Sprite m_sprite;
	PropertyMap* m_properties;
	int m_height;
	int m_width;
	int m_gid;
	bool m_walkable;
	bool m_visible;
};

#endif