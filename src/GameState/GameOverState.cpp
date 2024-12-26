#include <GameOverState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <SFML/System/Time.hpp>

GameOverState::GameOverState(StateStack& stack, Context context) : State(stack, context) {
    mBackground.setSize(sf::Vector2f(1280, 640));
    mBackground.setFillColor(sf::Color(0, 0, 0, 128));
    mBackground.setPosition(0, 0);

    mBoard.setTexture(context.textures->get(Textures::GameOverBoard));
    mBoard.setPosition(390, 66);

    mRestartButton.setTexture(context.textures->get(Textures::GameOverRestartButton));
    mRestartButton.setPosition(660, 478);

    mMenuButton.setTexture(context.textures->get(Textures::GameOverMenuButton));
    mMenuButton.setPosition(570, 478);

    context.music->setVolume(80);
	context.music->play(Music::GameOverTheme);
}

void GameOverState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackground);
    window.draw(mBoard);
    window.draw(mRestartButton);
    window.draw(mMenuButton);
}

bool GameOverState::update(sf::Time deltatime) {
    return false;
}

bool GameOverState::handleEvent(const sf::Event& event) {

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (mMenuButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                requestStackPush(States::TransitionMenu);
            }
            else if (mRestartButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                requestStackPop();
                requestStackPush(States::TransitionGame_2);
            }
        }
    }

    return false;
}
