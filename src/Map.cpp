#include "Map.h"
#include "render.h"
#include <fstream>

Map::Map(const std::string& filePath, int tileSize, sf::Texture& texture)
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
        }
    }
}

void Map::draw(sf::RenderWindow& window) {
    for (int i = 0; i < mapData.size(); ++i) {
        for (int j = 0; j < mapData[i].size(); ++j) {
            char tileType = mapData[i][j];

            // Define tile texture regions based on tile type
            if (tileType == '1') { // Solid block
                tile.setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));  // Assuming the first tile is a solid block
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
