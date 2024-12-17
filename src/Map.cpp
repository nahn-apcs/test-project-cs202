#include "Map.h"
#include "render.h"
#include <fstream>

Map::Map(const std::string& filePath, int tileSize, std::vector<sf::Texture>& mapTexture)
    : tileSize(tileSize)
{
    coinsNumber = 0;
    monsterNumber = 0;
    coinCount = 0;
    score = 0;
    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line)) {
        mapData.push_back(line);
    }

    //sf::Texture projectTile;
    if (mapTexture.size() > 2) {
        texture = mapTexture[0];
        Monstertexture = mapTexture[1];
        projectTile = mapTexture[2];
    }
    tile.setTexture(texture);
    tile.setTextureRect(sf::IntRect(0, 0, constants::scene_width, constants::scene_height)); // Select first tile
    //sf::Sprite coinTexture = tile;
    //coinTexture.setTextureRect(sf::IntRect(9*32, 32, tileSize, tileSize)); 
    for (int i = 0; i < mapData.size(); ++i) {
        for (int j = 0; j < mapData[i].size(); ++j) {
            if (mapData[i][j] == 'C') {
                // Create a coin at the corresponding position
                Item* temp = ItemFactory::createItem("Coin", texture, { j * tileSize, i * tileSize });
                coins.push_back(temp);
				coinsNumber++;
            }

            if (mapData[i][j] == '5') {
                Block* block = BlockFactory::createBlock("brick", texture, { j * tileSize, i * tileSize });
                blocks.push_back(block);
              
            }
            if (mapData[i][j] == '7') {
                Block* block = BlockFactory::createBlock("question", texture, { j * tileSize, i * tileSize });
                blocks.push_back(block);
          
                block->setItem("coin");
              
            }
            if (mapData[i][j] == '8') {
                Block* block = BlockFactory::createBlock("question", texture, { j * tileSize, i * tileSize });
                blocks.push_back(block);
       
                block->setItem("peach");
            }


            if (mapData[i][j] == 'M') {
              Monster* monster = MonsterFactory::createMonster("Goomba", Monstertexture, { j * tileSize, i * tileSize });
              monsters.push_back(monster);
              mapData[i][j] = '0';
			  monsterNumber++;

            }
            if (mapData[i][j] == 'B') {
              Monster* monster = MonsterFactory::createMonster("Bee", Monstertexture, { j * tileSize, i * tileSize });
              monsters.push_back(monster);
              mapData[i][j] = '0';
              monsterNumber++;

            }
            if (mapData[i][j] == 'b') {
              Monster* monster = MonsterFactory::createMonster(
                "bee", Monstertexture, { j * tileSize, i * tileSize });
             
                monsters.push_back(monster);
                mapData[i][j] = '0';
                monsterNumber++;

            }

        }
    }
   
}

void Map::draw(sf::RenderWindow& window) {
    for (auto& monster : monsters) {
        monster->draw(window);
    }
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
            //else if (tileType == '5')
            //{
            //    tile.setTextureRect(sf::IntRect(32, 0, tileSize, tileSize));  // Assuming the first tile is a solid bloc
            //}
            //else if (tileType == '7' || tileType == '8') {
            //    tile.setTextureRect(sf::IntRect(32*6, 32, tileSize, tileSize));  // Assuming the first tile is a solid block
            //}
            else if (tileType == 'P')
            {
                tile.setTextureRect(sf::IntRect(16*32, 32, tileSize, tileSize));  // Assuming the first tile is a solid bloc
            }
            else if (tileType == 'p') {
                tile.setTextureRect(sf::IntRect(17*32, 32, tileSize, tileSize));  // Assuming the first tile is a solid bloc
            }
            else if (tileType == 'H') {
                tile.setTextureRect(sf::IntRect(16*32, 0, tileSize, tileSize));  // Assuming the first tile is a solid bloc
            }
            else if (tileType == 'h')
            {
                tile.setTextureRect(sf::IntRect(17*32, 0, tileSize, tileSize));  // Assuming the first tile is a solid block

            }
            else /*if (tileType == '0' || tileType == 'C')*/ { // Empty space (no drawing needed)
                continue;
            }


            tile.setPosition(j * tileSize, i * tileSize);
            window.draw(tile);
        }
    }

    for (auto& coin : coins) {
        coin->draw(window);
    }

    for (auto& block : blocks) {
        block->draw(window);
    }

    projectiles.draw(window);


	//sf::Font font;
	//font.loadFromFile("../resources/font/Pixel_NES.otf");
	//sf::Text text;
	//text.setFont(font);
	//text.setString("Coins: " + std::to_string(coinCount));
	//text.setCharacterSize(24);
	//text.setFillColor(sf::Color::Black);
	//text.setPosition(10, 10);
}

void Map::updateCoins(const sf::FloatRect& playerBounds, float deltatime) {
    // Check for coin collection
    
    for (auto& coin : coins) {
        coin->update(deltatime, mapData, 32);
        if (coin->getBounds().intersects(playerBounds) && !coin->isCollected()) {
            coin->collect(); // Collect the coin
          if (dynamic_cast<Coin*>(coin)) {
            coinCount++;
          }
          else if (dynamic_cast<PowerUp*>(coin)) {
            //implement power up
          }
			      
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
    for (int i = 0; i < projectiles.getProjectiles().size(); ++i) {
       
            if (projectiles.getProjectiles()[i]->getBounds().intersects(monsterBounds)) {
                projectiles.destroyProjectile(i);
                auto tileX = static_cast<int>(monsterBounds.left / tileSize);
                auto tileY = static_cast<int>(monsterBounds.top / tileSize);

                mapData[tileY][tileX] = '0';
                monster->kill(true, monster);  
            }
        
    }

    // Check intersection
    if (monsterBounds.intersects(playerBounds)) {
      //std::cout<< "Monster collision detected" << std::endl;
      // Check if the player is above the monster
      float playerBottom =
        playerBounds.top + playerBounds.height;  // Bottom of the player
      float monsterTop = monsterBounds.top;      // Top of the monster


      if (playerBottom <= monsterTop + 5.0f) {  // Allow a small tolerance
        // Monster is killed
        auto tileX = static_cast<int>(monsterBounds.left / tileSize);
        auto tileY = static_cast<int>(monsterBounds.top / tileSize);
       
        mapData[tileY][tileX] = '0';
        monster->kill(true, monster);  // Kill the monster

      }  
      else {
          //std::cout<< "Player is killed" << std::endl;
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

void Map::printMapData() const
{
	for (int i = 0; i < mapData.size(); ++i) {
		for (int j = 0; j < mapData[i].size(); ++j) {
			std::cout << mapData[i][j];
		}
		std::cout << std::endl;
	}
}

void Map::saveMapData(const std::string& filePath) {
    // Print debug information
    std::cout << "Saving map data to: " << filePath << std::endl;

    // Open the file
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file: " << filePath << std::endl;
        return;
    }

    // Check mapData size
    if (mapData.empty()) {
        std::cerr << "Warning: mapData is empty. No data will be written." << std::endl;
    }

    // Write data
    for (const auto& data : mapData) {
        file << data << '\n';
    }

    // Optional flush
    file.flush();
    std::cout << "Map data saved successfully." << std::endl;
}


bool Map::isVissible(const sf::Sprite& sprite, const sf::View& camera)
{
  sf::FloatRect monsterBounds = sprite.getGlobalBounds();
  sf::FloatRect viewBounds(camera.getCenter() - camera.getSize() / 2.1f,
                           camera.getSize());
  return monsterBounds.intersects(viewBounds);
}


bool Map::colliable(int x, int y) const
{
    if (x < 0 || y < 0 || x >= mapData[0].size() || y >= mapData.size())
    {
        return false;
    }
    if (mapData[y][x] == '1' || mapData[y][x] == '2' || mapData[y][x] == '5' || mapData[y][x] == '7' || mapData[y][x] == '8' || mapData[y][x] == 'P' || mapData[y][x] == 'p' || mapData[y][x] == 'H' || mapData[y][x] == 'h')
    {
        return false;
    }
    return true;
}

bool Map::colliableChar(const char& c) const
{
    if (c == '1' || c == '2' || c == '5' || c == '7' || c == '8' || c == 'P' || c == 'p' || c == 'H' || c == 'h')
    {
        return false;
    }
    return true;
}

void Map::updateScore()
{   
	int coi = 0;
	for (auto& coin : coins) {
		if (coin->isCollected()) {
			coi++;
		}
	}
	int mons = 0;
	for (auto& monster : monsters) {
		if (monster->getIsKilled()) {
			mons++;
		}
	}
   for (auto& block : blocks) {
          auto item = block->getItemObject();
          if (dynamic_cast<Coin*>(item)) {
            if (item->isCollected()) {
              coi++;
       }
     }
   }

	score = coi * 100 + mons * 200;
}

void Map::updateBlocks(float deltatime,const sf::FloatRect& playerBounds)
{
 // std::cout << playerBounds.top << std::endl;
  for (auto it = blocks.begin(); it != blocks.end();) {
    auto& block = *it;
    block->update(deltatime, mapData, tileSize);
    if (block->isCollission(playerBounds)) {
     
      float playerTop = playerBounds.top;
      float blockBottom = block->getBounds().top + block->getBounds().height;
      float dy = blockBottom - playerTop;
      if (dy < 5.0f) {
        if (!block->getIsTouched()) {
          if (dynamic_cast<QuestionBlock*>(block)) {
            block->setState(new ActiveState());
            block->onTouch2(mapData, tileSize, texture);
            auto item = block->getItemObject();
            if (dynamic_cast<Coin*>(item)) {
  
              coinCount++;
            }
            else if (dynamic_cast<PowerUp*>(item)) {
              coins.push_back(item);
            }
          }
          
        }
      }
    }
   

    it++;
  }

}
void Map::updateProjectiles(float deltatime)
{
   
    for (int i = 0; i < projectiles.getProjectiles().size(); ++i) {
		int LeftX = projectiles.getProjectiles()[i]->getBounds().left/tileSize;
        int RightX = (projectiles.getProjectiles()[i]->getBounds().left + projectiles.getProjectiles()[i]->getBounds().width) / tileSize;
        int TopY = projectiles.getProjectiles()[i]->getBounds().top / tileSize;
        int BottomY = (projectiles.getProjectiles()[i]->getBounds().top + projectiles.getProjectiles()[i]->getBounds().height) / tileSize;
        int midY = (TopY + BottomY) / 2;
        if (RightX >= mapData[0].size()-1) {
			projectiles.destroyProjectile(i);
		}
        if (LeftX <= 0) {  
            projectiles.destroyProjectile(i);
        }
        if (!colliable(LeftX, midY) || !colliable(RightX, midY)) {
            projectiles.destroyProjectile(i);
        }
	}

  projectiles.update(deltatime);
}