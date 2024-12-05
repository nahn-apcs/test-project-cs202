#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Coin.h"


class Map {
public:
    Map(const std::string& filePath, int tileSize, sf::Texture& texture);
    void draw(sf::RenderWindow& window);
    std::vector<std::string> getMapData() const;
    int getTileSize() const { return tileSize; }
    void updateCoins(const sf::FloatRect& playerBounds);

private:
    std::vector<std::string> mapData;
    sf::Sprite tile;
    int tileSize;
    std::vector<Coin> coins;
};

#endif // MAP_H
