#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Coin.h"
#include"Monster.h"


class Map {
public:
    Map(const std::string& filePath, int tileSize, sf::Texture& texture,sf::Texture& Monstertexture);
    void draw(sf::RenderWindow& window);
    std::vector<std::string> getMapData() const;
    int getTileSize() const { return tileSize; }
    void updateCoins(const sf::FloatRect& playerBounds, float t);
    void updateMonsters(float deltatime, const sf::FloatRect& playerBounds, const sf::View& camera);
    bool isVissible(const sf::Sprite& sprite, const sf::View &camera);

    bool colliable(int x, int y) const;
    bool colliableChar(const char& c) const;
    int coinCount;

  private:
    const std::string notCollidable = "0C";
    std::vector<std::string> mapData;
    sf::Sprite tile;
    int tileSize;
    std::vector<Coin*> coins;
    std::vector<Monster*> monsters;
};

#endif // MAP_H
