#ifndef MAPRENDERER_H
#define MAPRENDERER_H

#include <SFML/Graphics.hpp>

class MapRenderer {
private:
    sf::Texture mapTexture;
    sf::Sprite mapSprite;

public:
    MapRenderer(std::string initialMap);
    void updateMap(std::string newMap);
    void render(sf::RenderWindow& window);
};

#endif