#include <GameState.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <SFML/System/Time.hpp>
#include "AudioManagement.h"

GameState::GameState(StateStack& stack, Context context, int level, int character) : State(stack, context), character(character) {
	monsterset = context.textures->get(Textures::Enemies);
	projectile = context.textures->get(Textures::Bullet);
	camera = sf::View(sf::FloatRect(0.f, 0.f, constants::scene_width, constants::scene_height));
	std::cout << "GameState" << "\n";
	drawEngine = new DrawEngine();
	
	switch (character)
	{
	case 1:
		std::cout << "GameState 1" << "\n";

		idleTextures.push_back(context.textures->get(Textures::WukongStand1));
		idleTextures.push_back(context.textures->get(Textures::WukongStand2));
		idleTextures.push_back(context.textures->get(Textures::WukongStand3));
		idleTextures.push_back(context.textures->get(Textures::WukongStand4));
		
		runTextures.push_back(context.textures->get(Textures::WukongRun1));
		runTextures.push_back(context.textures->get(Textures::WukongRun2));
		runTextures.push_back(context.textures->get(Textures::WukongRun3));
		runTextures.push_back(context.textures->get(Textures::WukongRun4));

		jumpTextures.push_back(context.textures->get(Textures::WukongJump1));
		jumpTextures.push_back(context.textures->get(Textures::WukongJump2));
		jumpTextures.push_back(context.textures->get(Textures::WukongJump3));
		jumpTextures.push_back(context.textures->get(Textures::WukongJump4));
		std::cout << "GameState 22" << "\n";

		attackTextures.push_back(context.textures->get(Textures::WukongAttack1));
		attackTextures.push_back(context.textures->get(Textures::WukongAttack2));

		sIdleTextures.push_back(context.textures->get(Textures::SmallWukongStand1));
		sIdleTextures.push_back(context.textures->get(Textures::SmallWukongStand2));
		sIdleTextures.push_back(context.textures->get(Textures::SmallWukongStand3));
		sIdleTextures.push_back(context.textures->get(Textures::SmallWukongStand4));
		std::cout << "GameState 33" << "\n";

		sRunTextures.push_back(context.textures->get(Textures::SmallWukongRun1));
		sRunTextures.push_back(context.textures->get(Textures::SmallWukongRun2));
		sRunTextures.push_back(context.textures->get(Textures::SmallWukongRun3));
		sRunTextures.push_back(context.textures->get(Textures::SmallWukongRun4));

		deadTextures.push_back(context.textures->get(Textures::DeadWukong1));
		deadTextures.push_back(context.textures->get(Textures::DeadWukong2));
		deadTextures.push_back(context.textures->get(Textures::DeadWukong3));
		deadTextures.push_back(context.textures->get(Textures::DeadWukong4));
		deadTextures.push_back(context.textures->get(Textures::DeadWukong5));
		deadTextures.push_back(context.textures->get(Textures::DeadWukong6));
		deadTextures.push_back(context.textures->get(Textures::DeadWukong7));
		deadTextures.push_back(context.textures->get(Textures::DeadWukong8));
		deadTextures.push_back(context.textures->get(Textures::DeadWukong9));

		player = new Character(idleTextures, runTextures, attackTextures, jumpTextures, sIdleTextures, sRunTextures, sIdleTextures, sRunTextures, deadTextures, 100, 100);
		std::cout << "GameState 1.1" << "\n";

		break;
	default:
		break;
	}

	switch (level)
	{
		case 1:

			tileset = context.textures->get(Textures::Blocks);
			mapTextures.push_back(tileset);
			mapTextures.push_back(monsterset);
			mapTextures.push_back(projectile);
			gameMap = new Map("../resources/Level1/level.txt", 32, mapTextures);
			backgroundTexture = context.textures->get(Textures::Bg1);
			backgroundSprite.setTexture(context.textures->get(Textures::Bg1));
			std::cout << gameMap->getMapData().size() << "\n";
			xRepeatCount = gameMap->getMapData()[0].size() * 32 / backgroundTexture.getSize().x + 1;  // Add 1 to ensure coverage
			yRepeatCount = gameMap->getMapData().size() * 32 / backgroundTexture.getSize().y + 1;
              

			break;
    case 2:
      tileset = context.textures->get(Textures::Blocks2);
      mapTextures.push_back(tileset);
      mapTextures.push_back(monsterset);
      mapTextures.push_back(projectile);
      gameMap = new Map("../resources/Level2/level.txt", 32, mapTextures);
      backgroundTexture = context.textures->get(Textures::Bg2);
      backgroundSprite.setTexture(context.textures->get(Textures::Bg2));
      std::cout << gameMap->getMapData().size() << "\n";
      xRepeatCount = gameMap->getMapData()[0].size() * 32 / backgroundTexture.getSize().x + 1;  // Add 1 to ensure coverage
      yRepeatCount = gameMap->getMapData().size() * 32 / backgroundTexture.getSize().y + 1;

      break;
    case 3:
      tileset = context.textures->get(Textures::Blocks3);
      mapTextures.push_back(tileset);
      mapTextures.push_back(monsterset);
      mapTextures.push_back(projectile);
      gameMap = new Map("../resources/Level3/level.txt", 32, mapTextures);
      backgroundTexture = context.textures->get(Textures::Bg3);
      backgroundSprite.setTexture(context.textures->get(Textures::Bg3));
      std::cout << gameMap->getMapData().size() << "\n";
      xRepeatCount = gameMap->getMapData()[0].size() * 32 / backgroundTexture.getSize().x + 1;  // Add 1 to ensure coverage
      yRepeatCount = gameMap->getMapData().size() * 32 / backgroundTexture.getSize().y + 1;

      break;


	default:
		break;
	}
	std::cout << "GameState 2" << "\n";

}

bool GameState::update(sf::Time dt) {

	float deltaTime = gameClock.restart().asSeconds();
	sf::RenderWindow& window = *getContext().window;
	std::vector<std::string>& mapData = gameMap->getMapData();
	sf::FloatRect playerBounds = player->getBounds();
	std::vector<Monster*> monsters = gameMap->getMonsters();
	ProjectileManager& projectiles = gameMap->getProjectiles();
	AudioManagement* audioManager = gameMap->getAudioManager();
	int tileSize = gameMap->getTileSize();

	// Update camera position based on player position
	int mapWidth = gameMap->getMapData()[0].size() * gameMap->getTileSize();
	int mapHeight = gameMap->getMapData().size() * gameMap->getTileSize();

	// Make sure the camera stays within the bounds of the map
	float cameraX = std::max(constants::scene_width / 2.f, std::min(player->getBounds().left + player->getBounds().width / 2, mapWidth - constants::scene_width / 2.f));
	float cameraY = std::max(constants::scene_height / 2.f, std::min(player->getBounds().top + player->getBounds().height / 2, mapHeight - constants::scene_height / 2.f));

	camera.setCenter(cameraX, cameraY);
	window.setView(camera);


	// Update player and game state
	player->interact(deltaTime, gameMap);
	player->update(deltaTime, gameMap);


	//gameMap->updateCoins(player->getBounds(), deltaTime);
	std::vector<Item*> coins = gameMap->getCoins();
	for (auto& coin : coins) {
		coin->update(deltaTime, mapData, 32);
		if (coin->getBounds().intersects(playerBounds) && !coin->isCollected()) {
			audioManager->playCoinSound();
			coin->collect(); // Collect the coin
			if (dynamic_cast<Coin*>(coin)) {
				gameMap->increaseCoinsNumber();
			}
			else if (dynamic_cast<PowerUp*>(coin)) {
				player->levelUp(gameMap);
			}

		}
	}

	gameMap->updateScore();


	//gameMap->updateMonsters(deltaTime, player->getBounds(), camera);
	for (auto it = monsters.begin(); it != monsters.end();) {
		auto& monster = *it;  // Use reference for clarity and efficiency
		if (!gameMap->isVissible(monster->getSprite(), camera)) {
			++it;
			continue;
		}
		monster->update(deltaTime, mapData, tileSize);

		// Get player and monster positions
		sf::FloatRect monsterBounds = monster->getBounds();
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
		if (monsterBounds.intersects(playerBounds) && !monster->getIsKilled()) {
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
				player->knockUp();
				monster->kill(true, monster);  // Kill the monster

			}
			else {
				//std::cout<< "Player is killed" << std::endl;
				if (!monster->getIsKilled()) {
					player->damaged(gameMap);
				}
			}
		}

		++it;  // Increment the iterator if no monster was removed
	}



	//gameMap->updateBlocks(deltaTime,player->getBounds());
	std::vector<Block*> blocks = gameMap->getBlocks();
	for (auto it = blocks.begin(); it != blocks.end();) {
		auto& block = *it;
		block->update(deltaTime, mapData, tileSize);
		// playerBounds.left += 2.0f;
		if (block->isCollission(playerBounds) && !block->getIsDestroyed()) {
			float playerTop = playerBounds.top;
			float blockBottom = block->getBounds().top + block->getBounds().height;
			float dy = blockBottom - playerTop;
			if (dy < 5.0f) {
				if (!block->getIsTouched()) {
					if (dynamic_cast<QuestionBlock*>(block)) {
						block->setState(new ActiveState());
						block->onTouch2(mapData, tileSize, gameMap->getTexture());
						auto item = block->getItemObject();
						if (dynamic_cast<Coin*>(item)) {
							audioManager->playCoinSound();
							gameMap->increaseCoinsNumber();
						}
						else if (dynamic_cast<PowerUp*>(item)) {
							gameMap->addCoins(item);
						}
					}
					else if (dynamic_cast<BrickBlock*>(block) && player->isEvoled()) {
						block->setState(new DestroyedState());
						block->onTouch2(mapData, tileSize,
							gameMap->getTexture());
						int tileX = (block->getBounds().left + 5.0f) / tileSize;
						int tileY = (block->getBounds().top + 5.0f) / tileSize;
						std::cout << tileY << " " << tileX << std::endl;
						std::cout << mapData[tileY][tileX] << std::endl;
						mapData[tileY][tileX] = '0';
						block->setDestroyed(true);
					}
				}
			}
		}
		//Check flag
		if (dynamic_cast<FlagBlock*>(block)) {
			if (playerBounds.intersects(block->getBounds())) {
				std::cout << "Player win" << std::endl;
			}
			else if (playerBounds.left + playerBounds.width + 5 > block->getBounds().left && playerBounds.top + playerBounds.height > block->getBounds().top && playerBounds.left <  block->getBounds().left) {
				std::cout << "Player win" << std::endl;
			}
		}
		it++;
	}


	gameMap->updateProjectiles(deltaTime);

	return false;
}

void GameState::draw() {
	sf::RenderWindow& window = *getContext().window;
	window.setView(camera);
	for (int i = 0; i < xRepeatCount; ++i) {
		            for (int j = 0; j < yRepeatCount; ++j) {
		                backgroundSprite.setPosition(i * backgroundTexture.getSize().x, j * backgroundTexture.getSize().y);
		                window.draw(backgroundSprite); 
		            }
		        }
	gameMap->draw(window);
	player->draw(window);
	player->drawBounds(window);
	for (auto& monster : gameMap->getMonsters()) {
		monster->drawBounds(window);
	}
	drawEngine->displayGameInfo(window, timeClock, gameMap, player);
}

bool GameState::handleEvent(const sf::Event& event) {
	
	return false;
}















//MenuState::MenuState(StateStack& stack, Context context) : State(stack, context), mBackgroundSprite(), mGUIContainer(GUI::Container::TopDown) {
//    sf::Texture& texture = context.textures->get(Textures::MainMenuBG_1);
//    mBackgroundSprite.push_back(sf::Sprite(texture));
//
//    sf::Texture& texture_1 = context.textures->get(Textures::MainMenuBG_2);
//    mBackgroundSprite.push_back(sf::Sprite(texture_1));
//
//    sf::Texture& texture_2 = context.textures->get(Textures::MainMenuBG_3);
//    mBackgroundSprite.push_back(sf::Sprite(texture_2));
//
//    sf::Sprite tmp;
//
//    sf::Texture& texture_3 = context.textures->get(Textures::MainMenuClound_1);
//    tmp = sf::Sprite(texture_3);
//    tmp.setPosition(0, 37);
//    mCloundSprite.push_back(tmp);
//
//    sf::Texture& texture_4 = context.textures->get(Textures::MainMenuClound_2);
//    tmp = sf::Sprite(texture_4);
//    tmp.setPosition(475, 48);
//    mCloundSprite.push_back(tmp);
//
//    sf::Texture& texture_5 = context.textures->get(Textures::MainMenuClound_3);
//    tmp = sf::Sprite(texture_5);
//    tmp.setPosition(950, 37);
//    mCloundSprite.push_back(tmp);
//
//    sf::Texture& texture_6 = context.textures->get(Textures::MainMenuClound_4);
//    tmp = sf::Sprite(texture_6);
//    tmp.setPosition(0, 10);
//    mCloundSprite.push_back(tmp);
//
//    sf::Texture& texture_7 = context.textures->get(Textures::MainMenuClound_5);
//    tmp = sf::Sprite(texture_7);
//    tmp.setPosition(449, 3);
//    mCloundSprite.push_back(tmp);
//
//    sf::Texture& texture_8 = context.textures->get(Textures::MainMenuClound_6);
//    tmp = sf::Sprite(texture_8);
//    tmp.setPosition(897, 0);
//    mCloundSprite.push_back(tmp);
//
//    sf::Texture& texture_9 = context.textures->get(Textures::MainMenuClound_7);
//    tmp = sf::Sprite(texture_9);
//    tmp.setPosition(345, -9);
//    mCloundSprite.push_back(tmp);
//
//    sf::Texture& texture_10 = context.textures->get(Textures::MainMenuClound_8);
//    tmp = sf::Sprite(texture_10);
//    tmp.setPosition(759, -9);
//    mCloundSprite.push_back(tmp);
//
//
//    auto playButton = std::make_shared<GUI::Button>(context, Textures::button, 150, 45);
//    playButton->setPosition(565, 380);
//    playButton->setText("Play");
//    playButton->setCallback([this]() {
//        //requestStackPop();
//        requestStackPush(States::Level);
//        std::cout << "Play button pressed" << std::endl;
//        });
//
//    auto guideButton = std::make_shared<GUI::Button>(context, Textures::button, 150, 45);
//    guideButton->setPosition(565, 440);
//    guideButton->setText("Guide");
//    guideButton->setCallback([this]() {
//        //requestStackPop();
//        requestStackPush(States::Guide);
//        std::cout << "Guide button pressed" << std::endl;
//        });
//
//
//    auto settingButton = std::make_shared<GUI::Button>(context, Textures::button, 150, 45);
//    settingButton->setPosition(565, 500);
//    settingButton->setText("Setting");
//    settingButton->setCallback([this]() {
//        //requestStackPop();
//        //requestStackPush(States::Game);
//        std::cout << "Setting button pressed" << std::endl;
//        });
//
//    auto exitButton = std::make_shared<GUI::Button>(context, Textures::button, 150, 45);
//    exitButton->setPosition(565, 560);
//    exitButton->setText("Quit");
//    exitButton->setCallback([this]() {
//        requestStackPop();
//        });
//
//    mGUIContainer.pack(playButton);
//    mGUIContainer.pack(guideButton);
//    mGUIContainer.pack(settingButton);
//    mGUIContainer.pack(exitButton);
//
//    sf::Font& font = context.fonts->get(Fonts::NameGame);
//
//    wukongText.setFont(font);
//    wukongText.setString("Journey to the West");
//    wukongText.setCharacterSize(120);
//    wukongText.setFillColor(sf::Color(0, 0, 0, 255));
//    wukongText.setOrigin(wukongText.getLocalBounds().width / 2.0f, wukongText.getLocalBounds().height / 2.0f);
//    wukongText.setPosition(640, 150);
//    wukongText.setScale(mScale, mScale);
//
//    // Khởi tạo bóng của chữ
//    shadowText = wukongText; // Copy toàn bộ thuộc tính từ chữ chính
//    shadowText.setFillColor(sf::Color(0, 0, 0, 128)); // Màu đen mờ hơn
//    shadowText.setPosition(wukongText.getPosition().x + 5, wukongText.getPosition().y + 5); // Lệch vị trí
//
//}
//
//void MenuState::draw() {
//    sf::RenderWindow& window = *getContext().window;
//    window.setView(window.getDefaultView());
//
//    for (const sf::Sprite& sprite : mBackgroundSprite) {
//        window.draw(sprite);
//    }
//
//    for (int i = mCloundSprite.size() - 1; i >= 0; i--) {
//        sf::Sprite& sprite = mCloundSprite[i];
//        window.draw(sprite);
//    }
//
//    window.draw(mGUIContainer);
//
//
//
//    window.draw(shadowText);
//    window.draw(wukongText);
//}
//
//bool MenuState::update(sf::Time deltatime)
//{
//
//
//    if (mTextState == ScalingUp) {
//        float scaleSpeed = 0.5f * deltatime.asSeconds();
//        mScale += scaleSpeed;
//        if (mScale >= 1.0f) {
//            mScale = 1.0f;
//            mTextState = None;
//        }
//        wukongText.setScale(mScale, mScale);
//        shadowText.setScale(mScale, mScale);
//
//    }
//
//
//
//    for (int i = 0; i < mCloundSprite.size(); i++) {
//        sf::Sprite& sprite = mCloundSprite[i];
//        sprite.move(-speed[i] * deltatime.asSeconds(), 0);
//        if (sprite.getPosition().x < -sprite.getLocalBounds().width) {
//            sprite.setPosition(1280, sprite.getPosition().y);
//        }
//    }
//
//
//
//    return false;
//}
//
//bool MenuState::handleEvent(const sf::Event& event)
//{
//    mGUIContainer.handleEvent(event);
//    return false;}
