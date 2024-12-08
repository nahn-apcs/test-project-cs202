#include "Map.h"
#include "render.h"
#include <fstream>

Map::Map(const std::string& filePath, int tileSize, sf::Texture& texture, sf::Texture& Monstertexture)
    : tileSize(tileSize)
{
    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line)) {
        mapData.push_back(line);
    }
    tile.setTexture(texture);
    tile.setTextureRect(sf::IntRect(0, 0, constants::scene_width, constants::scene_height)); // Select first tile
    sf::Sprite coinTexture = tile;
    coinTexture.setTextureRect(sf::IntRect(9*32, 32, tileSize, tileSize)); 
    for (int i = 0; i < mapData.size(); ++i) {
        for (int j = 0; j < mapData[i].size(); ++j) {
            if (mapData[i][j] == 'C') {
                // Create a coin at the corresponding position
                coins.push_back(Coin(coinTexture, j * tileSize, i * tileSize));
            }
            if (mapData[i][j] == 'M') {
              Monster* monster =
                MonsterFactory::createMonster("Goomba", Monstertexture);
              monster->setPosition(j * tileSize, i * tileSize);
              monsters.push_back(monster);
            }
            if (mapData[i][j] == 'T') {
              Monster* monster =
                MonsterFactory::createMonster("Turtle", Monstertexture);
              monster->setPosition(j * tileSize, i * tileSize);
              monsters.push_back(monster);
            }
        }
    }
   
}

void Map::draw(sf::RenderWindow& window) {
    for (int i = 0; i < mapData.size(); ++i) {
        for (int j = 0; j < mapData[i].size(); ++j) {
            char tileType = mapData[i][j];

            // Define tile texture regions based on tile type
            if (tileType == '1') { // Solid block
                tile.setTextureRect(sf::IntRect(32*3, 0, tileSize, tileSize));  // Assuming the first tile is a solid block
            }
            else if (tileType == '2') {
                // Solid block
				tile.setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));  // Assuming the first tile is a solid block
            }
            else if (tileType == '5')
            {
                tile.setTextureRect(sf::IntRect(32, 0, tileSize, tileSize));  // Assuming the first tile is a solid bloc
            }
            else if (tileType == '7' || tileType == '8') {
                tile.setTextureRect(sf::IntRect(32*6, 32, tileSize, tileSize));  // Assuming the first tile is a solid block
            }
            else if (tileType == 'P')
            {
                tile.setTextureRect(sf::IntRect(16*32, 7*32, tileSize, tileSize));  // Assuming the first tile is a solid bloc
            }
            else if (tileType == 'p') {
                tile.setTextureRect(sf::IntRect(17*32, 7*32, tileSize, tileSize));  // Assuming the first tile is a solid bloc
            }
            else if (tileType == 'H') {
                tile.setTextureRect(sf::IntRect(16*32, 6*32, tileSize, tileSize));  // Assuming the first tile is a solid bloc
            }
            else if (tileType == 'h')
            {
                tile.setTextureRect(sf::IntRect(17*32, 6*32, tileSize, tileSize));  // Assuming the first tile is a solid block

            }
            else /*if (tileType == '0' || tileType == 'C')*/ { // Empty space (no drawing needed)
                continue;
            }


            tile.setPosition(j * tileSize, i * tileSize);
            window.draw(tile);
        }
    }

    for (auto& coin : coins) {
        coin.draw(window);
    }
    for (auto& monster : monsters) {
      monster->draw(window);
    }
}

void Map::updateCoins(const sf::FloatRect& playerBounds) {
    // Check for coin collection
    for (auto& coin : coins) {
        if (coin.getBounds().intersects(playerBounds) && !coin.isCollected()) {
            coin.collect(); // Collect the coin
            // Update the score here if necessary
        }
    }
}

std::vector<std::string> Map::getMapData() const {
	return mapData;
}

void Map::updateMonsters(float deltatime, const sf::FloatRect& playerBounds, const sf::View& camera)
{
  for (auto it = monsters.begin(); it != monsters.end();) {
    auto& monster = *it;  // Use reference for clarity and efficiency
    if (!isVissible(monster->getSprite(), camera)) {
      ++it;
      continue;
    }
    monster->update(deltatime, mapData, tileSize);

    // Get player and monster positions
    sf::FloatRect monsterBounds = monster->getSprite().getGlobalBounds();

    // Check intersection
    if (monsterBounds.intersects(playerBounds)) {
      // Check if the player is above the monster
      float playerBottom =
        playerBounds.top + playerBounds.height;  // Bottom of the player
      float monsterTop = monsterBounds.top;      // Top of the monster

      if (playerBottom <= monsterTop + 5.0f) {  // Allow a small tolerance
        // Monster is killed
        auto tileX = static_cast<int>(monsterBounds.left / tileSize);
        auto tileY = static_cast<int>(monsterBounds.top / tileSize);
       
        mapData[tileY][tileX] = '0';
        monster->kill(true, "M");  // Kill the monster
        if (monster->getIsKilled() && monster->isAnimationFinished()) {
          std::cout << "Monster is killed" << std::endl;
          
          it = monsters.erase(it);  // Remove the monster
          continue;  // Skip incrementing the iterator since we erased
        }
      }
      else {
        if (!monster->getIsKilled()) {
          // Player is killed
          std::cout << "Player is killed" << std::endl;
          // Implement player death here
        }
      
      }
    }

    ++it;  // Increment the iterator if no monster was removed
  }
}

bool Map::isVissible(const sf::Sprite& sprite, const sf::View& camera)
{
  sf::FloatRect monsterBounds = sprite.getGlobalBounds();
  sf::FloatRect viewBounds(camera.getCenter() - camera.getSize() / 2.f,
                           camera.getSize());
  return monsterBounds.intersects(viewBounds);
}
