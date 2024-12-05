#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Map {
public:
    Map(const std::string& filePath, int tileSize, sf::Texture& texture);
    void draw(sf::RenderWindow& window);
    std::vector<std::string> getMapData() const;
    int getTileSize() const { return tileSize; }
private:
    std::vector<std::string> mapData;
    sf::Sprite tile;
    int tileSize;
};

#endif // MAP_H
