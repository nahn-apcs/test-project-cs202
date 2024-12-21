#include <LevelState.hpp>
#include <Button.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>



LevelState::LevelState(StateStack& stack, Context context): State(stack, context), mBackgroundSprite(), mGUIContainer(GUI::Container::LeftRight) {
    sf::Texture& texture = context.textures->get(Textures::LevelBG);
    mBackgroundSprite.push_back(sf::Sprite(texture));

    LevelText.setFont(context.fonts->get(Fonts::Main));
    LevelText.setString("Choose Your Level");
    LevelText.setCharacterSize(50);
    LevelText.setFillColor(sf::Color(255, 255, 255, 255));
    LevelText.setOrigin(LevelText.getLocalBounds().width / 2.0f, LevelText.getLocalBounds().height / 2.0f);
    LevelText.setPosition(640, 100);

    auto level1Button = std::make_shared<GUI::Button>(context, Textures::TestLevel, 150, 200);
    level1Button->setPosition(101, 254);
    level1Button->setText("Level 1", 130);
    level1Button->setCallback([this] () {
        //requestStackPop();
        requestStackPush(States::Game1_1);
        std::cout << "Level 1 button pressed" << std::endl;
    });

    auto level2Button = std::make_shared<GUI::Button>(context, Textures::TestLevel, 150, 200);
    level2Button->setPosition(333, 254);
    level2Button->setText("Level 2", 130);
    level2Button->setCallback([this] () {
        //requestStackPop();
        requestStackPush(States::Game2_1);
        std::cout << "Level 2 button pressed" << std::endl;
    });

    auto level3Button = std::make_shared<GUI::Button>(context, Textures::TestLevel, 150, 200);
    level3Button->setPosition(565, 254);
    level3Button->setText("Level 3", 130);
    level3Button->setCallback([this] () {
        //requestStackPop();
        requestStackPush(States::Game3_1);
        std::cout << "Level 3 button pressed" << std::endl;
    });

    auto level4Button = std::make_shared<GUI::Button>(context, Textures::TestLevel, 150, 200);
    level4Button->setPosition(797, 254);
    level4Button->setText("Level 4", 130);
    level4Button->setCallback([this] () {
        //requestStackPop();
        requestStackPush(States::Game4_1);
        std::cout << "Level 4 button pressed" << std::endl;
    });

    auto level5Button = std::make_shared<GUI::Button>(context, Textures::TestLevel, 150, 200);
    level5Button->setPosition(1029, 254);
    level5Button->setText("Level 5", 130);
    level5Button->setCallback([this] () {
        //requestStackPop();
        requestStackPush(States::Game5_1);
        std::cout << "Level 5 button pressed" << std::endl;
    });

    mGUIContainer.pack(level1Button);
    mGUIContainer.pack(level2Button);
    mGUIContainer.pack(level3Button);
    mGUIContainer.pack(level4Button);
    mGUIContainer.pack(level5Button);


    mBackButton.setTexture(context.textures->get(Textures::TestLevel));
    mBackButton.setTextureRect(sf::IntRect(0, 0, 80, 50));
    mBackButton.setPosition(0, 590);


}

void LevelState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    for(const sf::Sprite& sprite: mBackgroundSprite) {
        window.draw(sprite);
    }

    window.draw(LevelText);
    window.draw(mBackButton);


    window.draw(mGUIContainer);
}

bool LevelState::update(sf::Time deltatime)
{
    elapsedTime += deltatime.asSeconds();
    float scale = 1.0f + std::sin(elapsedTime * 5.f) * 0.05f; // Giá trị từ 0.95 -> 1.
    LevelText.setScale(scale, scale);
	return false;
}

bool LevelState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);

    if(event.type == sf::Event::MouseButtonPressed) {
        if(event.mouseButton.button == sf::Mouse::Left) {
            if(mBackButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                requestStackPop();
            }
        }
    }

	return false;
}