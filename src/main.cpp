#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Character.h"
#include "Physics.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include "render.h"
#include "DrawEngine.h"

const int TILE_SIZE = 32;

int main() {
    sf::RenderWindow window(sf::VideoMode(constants::scene_width, constants::scene_height), "Mario Game");

    // Load textures
    sf::Texture tileset, playerTexture, monsterset;
    if (!tileset.loadFromFile("../resources/blocks.png")
        || !playerTexture.loadFromFile("../resources/atk wk 2_sprite_2.png")
        || !monsterset.loadFromFile("../resources/Run-Sheet.png")) {
        return -1;
    }
    std::vector<sf::Texture> runTextures(4);
    if (!runTextures[0].loadFromFile("../resources/run wk_sprite_1.png") ||
        !runTextures[1].loadFromFile("../resources/run wk_sprite_2.png") ||
        !runTextures[2].loadFromFile("../resources/run wk_sprite_3.png") ||
        !runTextures[3].loadFromFile("../resources/run wk_sprite_4.png")) {
        return -1;  // Error loading run textures
    }

    // Create map and character
    Map gameMap("../resources/level.txt", TILE_SIZE, tileset, monsterset);
    Character player(playerTexture, runTextures, 100, 100);

    sf::View camera(sf::FloatRect(0.f, 0.f, constants::scene_width, constants::scene_height));
    camera.setCenter(player.getBounds().left + player.getBounds().width / 2, player.getBounds().top + player.getBounds().height / 2);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../resources/bg.png")) {
        return -1; // Error loading the texture
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    // Get the size of the screen
    int screenWidth = window.getSize().x;
    int screenHeight = window.getSize().y;

    // Calculate the number of repetitions
    int xRepeatCount = gameMap.getMapData()[0].size() * 32 / backgroundTexture.getSize().x + 1;  // Add 1 to ensure coverage
    int yRepeatCount = gameMap.getMapData().size() * 32 / backgroundTexture.getSize().y + 1;

    sf::Font font;
    if (!font.loadFromFile("../resources/font/Pixel_NES.otf")) { // Replace with the correct font path
        return -1; // Error loading font
    }

    //sf::Text messageText;
    //messageText.setFont(font);
    //messageText.setCharacterSize(24);
    //messageText.setFillColor(sf::Color::Blue);
    //messageText.setPosition(10.f, 10.f);
    //messageText.setString("Coins: ");

    //// Game clock for updating player and other mechanics (deltaTime)
    sf::Clock gameClock;

    //// Clock for tracking total time passed
    sf::Clock timeClock;

    //sf::Text timeText;
    //timeText.setFont(font);
    //timeText.setCharacterSize(24);
    //timeText.setFillColor(sf::Color::Blue);
    //timeText.setPosition(10, 40);
	DrawEngine drawEngine;
    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Get elapsed time since last frame (deltaTime)
        float deltaTime = gameClock.restart().asSeconds();

        // Update player and game state
        player.interact(deltaTime, gameMap);
        player.update(deltaTime, gameMap);
        gameMap.updateCoins(player.getBounds());

        // Update camera position based on player position
        int mapWidth = gameMap.getMapData()[0].size() * gameMap.getTileSize();
        int mapHeight = gameMap.getMapData().size() * gameMap.getTileSize();

        // Make sure the camera stays within the bounds of the map
        float cameraX = std::max(constants::scene_width / 2.f, std::min(player.getBounds().left + player.getBounds().width / 2, mapWidth - constants::scene_width / 2.f));
        float cameraY = std::max(constants::scene_height / 2.f, std::min(player.getBounds().top + player.getBounds().height / 2, mapHeight - constants::scene_height / 2.f));

        camera.setCenter(cameraX, cameraY);
        window.setView(camera);
      
        gameMap.updateMonsters(deltaTime, player.getBounds(), camera);


        // Update the time display
        //sf::Time elapsedTime = timeClock.getElapsedTime();
        //int seconds = static_cast<int>(elapsedTime.asSeconds()); // Convert time to seconds
        //timeText.setString("Time: " + std::to_string(seconds) + "s"); // Update the text with elapsed time

		// Display the game info
		//drawEngine.displayGameInfo(window, timeClock);
        // Clear the window
        window.clear();
        for (int i = 0; i < xRepeatCount; ++i) {
            for (int j = 0; j < yRepeatCount; ++j) {
                backgroundSprite.setPosition(i * backgroundTexture.getSize().x, j * backgroundTexture.getSize().y);
                window.draw(backgroundSprite);  // Draw each tile of the background
            }
        }

        // Draw the map and player
        gameMap.draw(window);
        player.draw(window);
        player.drawBounds(window);
        //gameMap.updateMonsters(deltaTime, player.getBounds());

        //window.setView(window.getDefaultView());

        // Draw the message and time
        /*window.draw(messageText);
        window.draw(timeText);*/
		drawEngine.displayGameInfo(window, timeClock);

        // Display everything on the window
        window.display();
    }

    return 0;
}





//#include <SFML/Graphics.hpp>
//#include "render.h"
//#include <fstream>
//#include <vector>
//
//class Map {
//public:
//    Map(const std::string& filePath, int tileSize, sf::Sprite& texture) {
//        std::ifstream file(filePath);
//        std::string line;
//        while (std::getline(file, line)) {
//            mapData.push_back(line);
//        }
//
//        tile = texture;
//        this->tileSize = tileSize;
//    }
//
//    void draw(sf::RenderWindow& window) {
//        for (int i = 0; i < mapData.size(); ++i) {
//            for (int j = 0; j < mapData[i].size(); ++j) {
//                char tileType = mapData[i][j];
//                if (tileType == '1') {
//                    tile.setPosition(j * tileSize, i * tileSize);
//                    window.draw(tile);
//                }
//            }
//        }
//    }
//
//private:
//    std::vector<std::string> mapData;
//    sf::Sprite tile;
//    int tileSize;
//};
//
//class Character {
//public:
//    Character(sf::Texture& texture, int x, int y) {
//        sprite.setTexture(texture);
//        sprite.setPosition(x, y);
//    }
//
//    void move(float dx, float dy) {
//        sprite.move(dx, dy);
//    }
//
//    void draw(sf::RenderWindow& window) {
//        window.draw(sprite);
//    }
//
//    sf::FloatRect getBounds() {
//        return sprite.getGlobalBounds();
//    }
//
//private:
//    sf::Sprite sprite;
//};
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode(constants::scene_width, constants::scene_height), "Mario Game");
//
//    // Load the tileset texture
//    sf::Texture tileset;
//    if (!tileset.loadFromFile("../resources/blocks.png")) {
//        return -1; // Error loading the texture
//    }
//
//    // Define tile dimensions
//    const int TILE_WIDTH = 32;
//    const int TILE_HEIGHT = 32;
//
//    // Create a sprite for the first tile
//    sf::Sprite tileTexture;
//    tileTexture.setTexture(tileset);
//    tileTexture.setTextureRect(sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT)); // Select first tile
//    sf::Texture playerTexture;
//    playerTexture.loadFromFile("../resources/atk wk 2_sprite_2.png");
//    // Create map and set view
//    Map gameMap("../resources/level.txt", 32, tileTexture);
//
//    Character player(playerTexture, 100, 100);
//
//    // Game loop
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        // Handle movement (without collisions for now)
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
//            player.move(-1, 0);
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
//            player.move(1, 0);
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
//            player.move(0, -1);
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
//            player.move(0, 1);
//        }
//
//        // Clear the window and draw everything
//        window.clear();
//        gameMap.draw(window);
//        player.draw(window);
//        window.display();
//    }
//
//    return 0;
//}
