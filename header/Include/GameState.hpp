#pragma once

#include <SFML/Graphics.hpp>

#include <State.hpp>
#include <Container.hpp>
#include <vector>

#include <SFML/Audio.hpp>
#include "Map.h"
#include "Character.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include "render.h"
#include "DrawEngine.h"
#include "Sound.h"
#include "Map.h"
#include "AudioManagement.h"
#include <fstream>
#include "constant.h"


class GameState : public State {

public:
    GameState(StateStack& stack, Context context, int level = 1, int charac =1);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:

    int level = 1;

  /*  std::vector<sf::Sprite> mBackgroundSprite;
    std::vector<sf::Sprite> mCloundSprite;
    GUI::Container mGUIContainer;

    sf::Text wukongText;
    sf::Text shadowText;
    float mScale = 0.1f;
    float mWukongAlpha = 255;
    bool mFadingOut = true;
    TextState mTextState = ScalingUp;*/
    //    // Load textures
//    sf::Texture tileset, playerTexture, monsterset, projectile;
//    if (!tileset.loadFromFile("../resources/level1/blocks.png")
//        || !playerTexture.loadFromFile("../resources/atk wk 2_sprite_2.png")
//        || !monsterset.loadFromFile("../resources/Run-sheet.png")
//        || !projectile.loadFromFile("../resources/bullet1_strip.png")
//        ) {
//        return -1;
//    }

    sf::Texture tileset, playerTexture, monsterset, projectile;
    sf::Sprite backgroundSprite;
    std::vector<sf::Texture> runTextures;
    std::vector<sf::Texture> attackTextures;
    std::vector<sf::Texture> mapTextures;
    Map gameMap;   
    Character* player;
    DrawEngine drawEngine;
    sf::Clock gameClock;
    sf::Clock timeClock;
    float elapsedTime = 0;
    int character = 1;
    int xRepeatCount, yRepeatCount;
    sf::Texture backgroundTexture;
    sf::View camera;

};





//
//const int TILE_SIZE = 32;
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode(constants::scene_width, constants::scene_height), "Mario Game", sf::Style::Close);
//    //sf::Music backgroundMusic;
//    //if (!backgroundMusic.openFromFile("../resources/Journey to the West.ogg")) {
//    //    return -1; // Error loading the music
//    //}
//
//    Sound backgroundSound;
//	std::string filePath = "../resources/Journey to the West.ogg";
//	//backgroundSound.playBackgroundMusic(filePath);
//	AudioManagement audioManager;
//	audioManager.playMainMusic();
//    // Set the music to loop and play it once
//    //backgroundMusic.setLoop(true);
//    //backgroundMusic.play();
//
//    // Load textures
//    sf::Texture tileset, playerTexture, monsterset, projectile;
//    if (!tileset.loadFromFile("../resources/level1/blocks.png")
//        || !playerTexture.loadFromFile("../resources/atk wk 2_sprite_2.png")
//        || !monsterset.loadFromFile("../resources/Run-sheet.png")
//        || !projectile.loadFromFile("../resources/bullet1_strip.png")
//        ) {
//        return -1;
//    }
//
//    std::vector<sf::Texture> runTextures(4);
//    if (!runTextures[0].loadFromFile("../resources/run wk_sprite_1.png") ||
//        !runTextures[1].loadFromFile("../resources/run wk_sprite_2.png") ||
//        !runTextures[2].loadFromFile("../resources/run wk_sprite_3.png") ||
//        !runTextures[3].loadFromFile("../resources/run wk_sprite_4.png")) {
//        return -1;  // Error loading run textures
//    }
//
//    std::vector<sf::Texture> attackTextures(2);
//    if (!attackTextures[0].loadFromFile("../resources/atk wk 3_sprite_2.png") ||
//        !attackTextures[1].loadFromFile("../resources/atk wk 3_sprite_3.png")
//        ) {
//        return -1;  // Error loading run textures
//    }
//
//    std::vector<sf::Texture> mapTextures;
//    mapTextures.push_back(tileset);
//    mapTextures.push_back(monsterset);
//    mapTextures.push_back(projectile);
//
//    // Create map and character
//    Map gameMap("../resources/level.txt", TILE_SIZE, mapTextures);
//    Character player(playerTexture, runTextures, attackTextures, 100, 100);
//
//    sf::View camera(sf::FloatRect(0.f, 0.f, constants::scene_width, constants::scene_height));
//    camera.setCenter(player.getBounds().left + player.getBounds().width / 2, player.getBounds().top + player.getBounds().height / 2);
//
//    sf::Texture backgroundTexture;
//    if (!backgroundTexture.loadFromFile("../resources/bg.png")) {
//        return -1; // Error loading the texture
//    }
//    sf::Sprite backgroundSprite(backgroundTexture);
//
//    // Get the size of the screen
//    int screenWidth = window.getSize().x;
//    int screenHeight = window.getSize().y;
//
//    // Calculate the number of repetitions
//    int xRepeatCount = gameMap.getMapData()[0].size() * 32 / backgroundTexture.getSize().x + 1;  // Add 1 to ensure coverage
//    int yRepeatCount = gameMap.getMapData().size() * 32 / backgroundTexture.getSize().y + 1;
//
//    sf::Font font;
//    if (!font.loadFromFile("../resources/font/Pixel_NES.otf")) { // Replace with the correct font path
//        return -1; // Error loading font
//    }
//	sf::Clock gameClock;
//	sf::Clock timeClock;
//    DrawEngine drawEngine;
//    // Game loop
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        // Get elapsed time since last frame (deltaTime)
//        float deltaTime = gameClock.restart().asSeconds();
//
//        // Update player and game state
//        player.interact(deltaTime, gameMap);
//        player.update(deltaTime, gameMap);
//        gameMap.updateCoins(player.getBounds(), deltaTime);
//        gameMap.updateScore();
//
//        // Update camera position based on player position
//        int mapWidth = gameMap.getMapData()[0].size() * gameMap.getTileSize();
//        int mapHeight = gameMap.getMapData().size() * gameMap.getTileSize();
//
//        // Make sure the camera stays within the bounds of the map
//        float cameraX = std::max(constants::scene_width / 2.f, std::min(player.getBounds().left + player.getBounds().width / 2, mapWidth - constants::scene_width / 2.f));
//        float cameraY = std::max(constants::scene_height / 2.f, std::min(player.getBounds().top + player.getBounds().height / 2, mapHeight - constants::scene_height / 2.f));
//
//        camera.setCenter(cameraX, cameraY);
//        window.setView(camera);
//
//        gameMap.updateMonsters(deltaTime, player.getBounds(), camera);
//        gameMap.updateBlocks(deltaTime,player.getBounds());
//        gameMap.updateProjectiles(deltaTime);
//
//        // Clear the window
//        window.clear();
//        for (int i = 0; i < xRepeatCount; ++i) {
//            for (int j = 0; j < yRepeatCount; ++j) {
//                backgroundSprite.setPosition(i * backgroundTexture.getSize().x, j * backgroundTexture.getSize().y);
//                window.draw(backgroundSprite);  // Draw each tile of the background
//            }
//        }
//
//        // Draw the map and player
//        gameMap.draw(window);
//        player.draw(window);
//        player.drawBounds(window);
//
//        // Display game info
//        drawEngine.displayGameInfo(window, timeClock, gameMap);
//
//        // Display everything on the window
//        window.display();
//    }
//
//    std::string resourcePath = "../resources/Ouput.txt";
//
//    // Open the file
//    std::ifstream testFileTesting(resourcePath);
//    std::ofstream testFile;
//
//    testFile.open(resourcePath);
//
//    // Check if the file was opened successfully
//    if (testFile.is_open()) {
//        testFile << "Test data\n";
//        testFile.close();
//        std::cout << "File saved successfully at " << resourcePath << std::endl;
//    }
//    else {
//        std::cerr << "Failed to create test file at " << resourcePath << std::endl;
//    }
//
//    return 0;
//}

