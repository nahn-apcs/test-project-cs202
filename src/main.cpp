#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Character.h"
#include "Physics.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include "render.h"

const int TILE_SIZE = 32;

int main() {
    sf::RenderWindow window(sf::VideoMode(constants::scene_width,constants::scene_height), "Mario Game");

    // Load textures
    sf::Texture tileset, playerTexture;
    if (!tileset.loadFromFile("../resources/blocks.png") || !playerTexture.loadFromFile("../resources/atk wk 2_sprite_2.png")) {
        return -1;
    }

    // Create map and character
    Map gameMap("../resources/level.txt", TILE_SIZE, tileset);
    Character player(playerTexture, 100, 100);

    sf::View camera(sf::FloatRect(0.f, 0.f, constants::scene_width, constants::scene_height));
    camera.setCenter(player.getBounds().left + player.getBounds().width / 2, player.getBounds().top + player.getBounds().height / 2);

    sf::Clock clock;

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Get elapsed time
        float deltaTime = clock.restart().asSeconds();

        // Handle movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.move(-200.f * deltaTime, 0, gameMap); // Move left
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.move(200.f * deltaTime, 0, gameMap); // Move right
        }

        // Handle jump
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            player.jump();
        }

        // Update player
        player.update(deltaTime, gameMap);

        // Move the camera with the player (center the camera on the player)
        camera.setCenter(player.getBounds().left + player.getBounds().width / 2, player.getBounds().top + player.getBounds().height / 2);

        // Set the view of the window to the camera
        window.setView(camera);

        // Clear the window
        window.clear();

        // Draw the map and player
        gameMap.draw(window);
        player.draw(window);

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
