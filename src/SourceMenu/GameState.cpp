#include <GameState.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <SFML/System/Time.hpp>


GameState::GameState(StateStack& stack, Context context, int level, int character) : State(stack, context), character(character) {
	monsterset = context.textures->get(Textures::Enemies);
	projectile = context.textures->get(Textures::Bullet);
	camera = sf::View(sf::FloatRect(0.f, 0.f, constants::scene_width, constants::scene_height));
	std::cout << "GameState" << "\n";
	
	switch (character)
	{
	case 1:
		playerTexture = context.textures->get(Textures::WukongIdle);
		runTextures.push_back(context.textures->get(Textures::WukongRun1));
		runTextures.push_back(context.textures->get(Textures::WukongRun2));
		runTextures.push_back(context.textures->get(Textures::WukongRun3));
		runTextures.push_back(context.textures->get(Textures::WukongRun4));
		attackTextures.push_back(context.textures->get(Textures::WukongAttack1));
		attackTextures.push_back(context.textures->get(Textures::WukongAttack2));
		player = new Character(playerTexture, runTextures, attackTextures, 100, 100);
		std::cout << "GameState 1.1" << "\n";

		break;
	default:
		break;
	}

	switch (level)
	{
		case 1:
			std::cout << "GameState 2.1" << "\n";

			tileset = context.textures->get(Textures::Blocks);
			mapTextures.push_back(tileset);
			mapTextures.push_back(monsterset);
			mapTextures.push_back(projectile);
			gameMap = Map("../ resources / Level1 / level.txt", 32, mapTextures);
			backgroundTexture = context.textures->get(Textures::Bg1);
			backgroundSprite.setTexture(context.textures->get(Textures::Bg1));
			std::cout << gameMap.getMapData().size() << "\n";
			xRepeatCount = gameMap.getMapData()[0].size() * 32 / backgroundTexture.getSize().x + 1;  // Add 1 to ensure coverage
			yRepeatCount = gameMap.getMapData().size() * 32 / backgroundTexture.getSize().y + 1;
			std::cout << "GameState 2.2" << "\n";

			break;
	default:
		break;
	}
	std::cout << "GameState 2" << "\n";

}

bool GameState::update(sf::Time dt) {
	std::cout << "GameState 3" << "\n";

	float deltaTime = gameClock.restart().asSeconds();
	sf::RenderWindow& window = *getContext().window;
	        // Update player and game state
	        player->interact(deltaTime, gameMap);
	        player->update(deltaTime, gameMap);
	        gameMap.updateCoins(player->getBounds(), deltaTime);
	        gameMap.updateScore();
	
	        // Update camera position based on player position
	        int mapWidth = gameMap.getMapData()[0].size() * gameMap.getTileSize();
	        int mapHeight = gameMap.getMapData().size() * gameMap.getTileSize();
	
	        // Make sure the camera stays within the bounds of the map
	        float cameraX = std::max(constants::scene_width / 2.f, std::min(player->getBounds().left + player->getBounds().width / 2, mapWidth - constants::scene_width / 2.f));
	        float cameraY = std::max(constants::scene_height / 2.f, std::min(player->getBounds().top + player->getBounds().height / 2, mapHeight - constants::scene_height / 2.f));
		
	        camera.setCenter(cameraX, cameraY);
	        window.setView(camera);
	
	        gameMap.updateMonsters(deltaTime, player->getBounds(), camera);
	        gameMap.updateBlocks(deltaTime,player->getBounds());
	        gameMap.updateProjectiles(deltaTime);
			std::cout << "GameState 4" << "\n";

			return false;
}

void GameState::draw() {
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	window.draw(backgroundSprite);
	gameMap.draw(window);
	player->draw(window);
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
