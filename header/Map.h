#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Coin.h"
#include"Monster.h"
#include"Block.h"
#include "Projectile.h"
#include "AudioManagement.h"

class Map {
public:
    Map() = default;
    Map(const Map& other) = default;
    Map(const std::string& filePath, int tileSize, std::vector<sf::Texture>& text);
    ~Map();
    void draw(sf::RenderWindow& window);
    std::vector<std::string> getMapData() const;
	void printMapData() const;
	void saveMapData(const std::string& filePath);
    int getTileSize() const { return tileSize; }
    void updateCoins(const sf::FloatRect& playerBounds, float t);
    void updateMonsters(float deltatime, const sf::FloatRect& playerBounds, const sf::View& camera);
    bool isVissible(const sf::Sprite& sprite, const sf::View &camera);

    bool colliable(int x, int y) const;
    bool colliableChar(const char& c) const;
    int coinCount;
    int score;
	void updateScore();
    void updateBlocks(float deltatime, sf::FloatRect& playerBounds);
    void updateProjectiles(float deltatime);
    sf::Texture& getProjectileTexture ()  { return projectTile; }
    ProjectileManager projectiles;
    AudioManagement* audioManager;
    Map operator&=(const Map& other);
    std::vector<Block*> getBlocks() const { return blocks; }
    void increaseCoinsNumber(){ coinsNumber++; }
    void addCoins(Item* coin) { coins.push_back(coin); }
    sf::Texture& getTexture() { return texture; }
    std::vector<Item*> getCoins() const { return coins; }
    std::vector<Monster*> getMonsters() const { return monsters; }
    std::vector<Block*> getBlocks() { return blocks; }
    ProjectileManager& getProjectiles() { return projectiles; }
    AudioManagement* getAudioManager() { return audioManager; }
  private:
    const std::string notCollidable = "0C";
    std::vector<std::string> mapData;
    sf::Sprite tile;
    int tileSize;
    std::vector<Item*> coins;
    std::vector<Monster*> monsters;
    std::vector<Block*> blocks;
	int coinsNumber;
	int monsterNumber;
    sf::Texture texture;
    sf::Texture Monstertexture;
    sf::Texture projectTile;
};

#endif // MAP_H
