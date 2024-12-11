#include <MenuState.hpp>
#include <Button.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>

MenuState::MenuState(StateStack& stack, Context context): State(stack, context), mBackgroundSprite(), mGUIContainer() {
    sf::Texture& texture = context.textures->get(Textures::MainMenuBG);
    mBackgroundSprite.push_back(sf::Sprite(texture));

    auto playButton = std::make_shared<GUI::Button>(context);
    playButton->setPosition(565, 490);
    playButton->setText("Play");
    playButton->setCallback([this] () {
        //requestStackPop();
        //requestStackPush(States::Game);
        std::cout << "Play button pressed" << std::endl;
    });
    
    auto exitButton = std::make_shared<GUI::Button>(context);
    exitButton->setPosition(565, 552);
    exitButton->setText("Exit");
    exitButton->setCallback([this] () {
        requestStackPop();
    });

    mGUIContainer.pack(playButton);
    mGUIContainer.pack(exitButton);
}

void MenuState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    for(const sf::Sprite& sprite: mBackgroundSprite) {
        window.draw(sprite);
    }

    window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}