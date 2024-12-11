#include <MenuState.hpp>
#include <Button.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>

MenuState::MenuState(StateStack& stack, Context context): State(stack, context), mBackgroundSprite(), mGUIContainer() {
    sf::Texture& texture = context.textures->get(Textures::MainMenuBG_1);
    mBackgroundSprite.push_back(sf::Sprite(texture));

    sf::Texture& texture_1 = context.textures->get(Textures::MainMenuBG_2);
    mBackgroundSprite.push_back(sf::Sprite(texture_1));

    sf::Texture& texture_2 = context.textures->get(Textures::MainMenuBG_3);
    mBackgroundSprite.push_back(sf::Sprite(texture_2));

    sf::Sprite tmp;

    sf::Texture& texture_3 = context.textures->get(Textures::MainMenuClound_1);
    tmp = sf::Sprite(texture_3);
    tmp.setPosition(925, 77);
    mCloundSprite.push_back(tmp);

    sf::Texture& texture_4 = context.textures->get(Textures::MainMenuClound_2);
    tmp = sf::Sprite(texture_4);
    tmp.setPosition(1024, 37);
    mCloundSprite.push_back(tmp);

    sf::Texture& texture_5 = context.textures->get(Textures::MainMenuClound_3);
    tmp = sf::Sprite(texture_5);
    tmp.setPosition(323, 75);
    mCloundSprite.push_back(tmp);

    sf::Texture& texture_6 = context.textures->get(Textures::MainMenuClound_4);
    tmp = sf::Sprite(texture_6);
    tmp.setPosition(524, 0);
    mCloundSprite.push_back(tmp);

    sf::Texture& texture_7 = context.textures->get(Textures::MainMenuClound_5);
    tmp = sf::Sprite(texture_7);
    tmp.setPosition(173, -13);
    mCloundSprite.push_back(tmp);

    sf::Texture& texture_8 = context.textures->get(Textures::MainMenuClound_6);
    tmp = sf::Sprite(texture_8);
    tmp.setPosition(850, 9);
    mCloundSprite.push_back(tmp);

    sf::Texture& texture_9 = context.textures->get(Textures::MainMenuClound_7);
    tmp = sf::Sprite(texture_9);
    tmp.setPosition(-31, 35);
    mCloundSprite.push_back(tmp);

    sf::Texture& texture_10 = context.textures->get(Textures::MainMenuClound_8);
    tmp = sf::Sprite(texture_10);
    tmp.setPosition(374, -13);
    mCloundSprite.push_back(tmp);


    auto playButton = std::make_shared<GUI::Button>(context);
    playButton->setPosition(565, 380);
    playButton->setText("Play");
    playButton->setCallback([this] () {
        //requestStackPop();
        //requestStackPush(States::Game);
        std::cout << "Play button pressed" << std::endl;
    });

    auto settingButton = std::make_shared<GUI::Button>(context);
    settingButton->setPosition(565, 440);
    settingButton->setText("Setting");
    settingButton->setCallback([this] () {
        //requestStackPop();
        //requestStackPush(States::Game);
        std::cout << "Setting button pressed" << std::endl;
    });
    
    auto exitButton = std::make_shared<GUI::Button>(context);
    exitButton->setPosition(565, 500);
    exitButton->setText("Quit");
    exitButton->setCallback([this] () {
        requestStackPop();
    });

    mGUIContainer.pack(playButton);
    mGUIContainer.pack(settingButton);
    mGUIContainer.pack(exitButton);

    sf::Font& font = context.fonts->get(Fonts::NameGame);

    wukongText.setFont(font);
    wukongText.setString("Journey to the west");
    wukongText.setCharacterSize(110);
    wukongText.setFillColor(sf::Color::Black);

    // Căn chỉnh chữ ở giữa màn hình
    sf::FloatRect textBounds = wukongText.getLocalBounds();
    wukongText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                         textBounds.top + textBounds.height / 2.0f);
    wukongText.setPosition(640, 200);

}

void MenuState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    for(const sf::Sprite& sprite: mBackgroundSprite) {
        window.draw(sprite);
    }

    for(const sf::Sprite& sprite: mCloundSprite) {
        window.draw(sprite);
    }

    window.draw(mGUIContainer);
    window.draw(wukongText);
}

bool MenuState::update(sf::Time deltatime)
{
    for(int i = 0; i < mCloundSprite.size(); i++) {
        sf::Sprite& sprite = mCloundSprite[i];
        sprite.move(-speed * deltatime.asSeconds(), 0);
        if(sprite.getPosition().x < -sprite.getLocalBounds().width) {
            sprite.setPosition(1280, sprite.getPosition().y);
        }
    }

    if (fadingOut) {
        alpha -= static_cast<int>(200 * deltatime.asSeconds());
        if (alpha <= 50) {
            alpha = 50;
            fadingOut = false;
        }
    } 
    else {
        alpha += static_cast<int>(200 * deltatime.asSeconds());
        if (alpha >= 255) {
            alpha = 255;
            fadingOut = true;
        }
    }

    // Cập nhật màu chữ với alpha mới
    wukongText.setFillColor(sf::Color(0, 0, 0, alpha));


	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}