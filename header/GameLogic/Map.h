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
    Map(std::vector<std::string>& map, int tileSize, std::vector<sf::Texture>& mapTexture,
        int sscore,
        std::vector<char>& saveMonsterType,
        std::vector<std::pair< float, float>>& saveMonsterPos,
        std::vector<std::pair<float, float>>& savePlayerProjectilePos,
        std::vector<std::pair<float, float>>& saveMonsterProjectilePos,
        std::vector<int>& savePlayerProjectileDir,
        std::vector<int>& saveMonsterProjectileDir,
        std::vector<std::pair<float, float>>& savePlayerProjectileVel,
        std::vector<std::pair<float, float>>& saveMonsterProjectileVel,

        std::vector<std::pair<float, float>>& saveItemPos,
        std::vector<int>& saveItemType);
       


    ~Map();
    void draw(sf::RenderWindow& window);
    std::vector<std::string>& getMapData() ;
	void printMapData() const;
	void saveMapData(const std::string& filePath);
    int getTileSize() const { return tileSize; }
    void updateCoins(const sf::FloatRect& playerBounds, float t);
    void updateMonsters(float deltatime, const sf::FloatRect& playerBounds, const sf::View& camera);
    bool isVissible(const sf::Sprite& sprite, const sf::View &camera);

    bool colliable(int x, int y) const;
    bool colliableChar(const char& c) const;
    int getCoinsNumber() const { return coinsNumber; }
    int score;
    int level = 0;
	void updateScore();
    void updateBlocks(float deltatime, sf::FloatRect& playerBounds);
    void updateProjectiles(float deltatime);
    void updateEnemyProjectiles(float deltatime);
    sf::Texture& getProjectileTexture ()  { return projectTile; }
    ProjectileManager projectiles;
    ProjectileManager enemyProjectiles;
    AudioManagement* audioManager;
    Map operator&=(const Map& other);
    std::vector<Block*> getBlocks() const { return blocks; }
    void increaseCoinsNumber(){ coinsNumber++; }
    void addCoins(Item* coin) { coins.push_back(coin); }
    sf::Texture& getTexture() { return texture; }
    sf::Texture& getEnemyProjectileTexture() { return enemyProjectTile; }
    std::vector<Item*> getCoins() const { return coins; }
    std::vector<Monster*> getMonsters() const { return monsters; }
    std::vector<Block*> getBlocks() { return blocks; }
    ProjectileManager& getProjectiles() { return projectiles; }
    ProjectileManager& getEnemyProjectiles() { return enemyProjectiles; }
    AudioManagement* getAudioManager() { return audioManager; }
    void setcoinsNumber(int coinsNumber) { this->coinsNumber = coinsNumber; }
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
    float constantScore = 0;
    sf::Texture texture;
    sf::Texture Monstertexture;
    sf::Texture projectTile;
    sf::Texture enemyProjectTile;
};

#endif // MAP_H
