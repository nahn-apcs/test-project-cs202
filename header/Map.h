#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Coin.h"
#include"Monster.h"
#include"Block.h"
#include "Projectile.h"

class Map {
public:
    Map(const std::string& filePath, int tileSize, std::vector<sf::Texture>& text);
    void draw(sf::RenderWindow& window);
    std::vector<std::string> getMapData() const;
    int getTileSize() const { return tileSize; }
    void updateCoins(const sf::FloatRect& playerBounds, float t);
    void updateMonsters(float deltatime, const sf::FloatRect& playerBounds, const sf::View& camera);
    bool isVissible(const sf::Sprite& sprite, const sf::View &camera);

    bool colliable(int x, int y) const;
    bool colliableChar(const char& c) const;
    int coinCount;
    int score;
	void updateScore();
    void updateBlocks(float deltatime);
    void updateProjectiles(float deltatime);
    sf::Texture& getProjectileTexture ()  { return projectTile; }
    ProjectileManager projectiles;

  private:
    const std::string notCollidable = "0C";
    std::vector<std::string> mapData;
    sf::Sprite tile;
    int tileSize;
    std::vector<Coin*> coins;
    std::vector<Monster*> monsters;
    std::vector<Block*> blocks;
	int coinsNumber;
	int monsterNumber;
    sf::Texture texture;
    sf::Texture Monstertexture;
    sf::Texture projectTile;
};

#endif // MAP_H
