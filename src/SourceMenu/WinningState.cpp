#include <WinningState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <SFML/System/Time.hpp>
#include <LevelManager.hpp>

WinningState::WinningState(StateStack& stack, Context context) : State(stack, context) {
    mBackgroundSprite.setTexture(context.textures->get(Textures::WinningBG));
    mBackgroundSprite.setPosition(0, 0);

    mBoard.setTexture(context.textures->get(Textures::WinningBoard));
    mBoard.setPosition(390, 51);

    mRestartButton.setTexture(context.textures->get(Textures::WinningRestartButton));
    mRestartButton.setOrigin(mRestartButton.getLocalBounds().width / 2.0f, mRestartButton.getLocalBounds().height / 2.0f);
    mRestartButton.setPosition(640, 476);
}

void WinningState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackgroundSprite);
    window.draw(mBoard);
    window.draw(mRestartButton);
}

bool WinningState::update(sf::Time deltatime) {
    mRestartButton.rotate(200 * deltatime.asSeconds());
    return true;
}

bool WinningState::handleEvent(const sf::Event& event) {

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (mRestartButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                LevelManager::getInstance().resetLevels();
                requestStateClear();
                requestStackPush(States::Menu);
            }
        }
    }

    return false;
}
