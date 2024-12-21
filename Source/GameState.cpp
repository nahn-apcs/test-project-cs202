#include <GameState.hpp>
#include <Button.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <SFML/System/Time.hpp>


GameState::GameState(StateStack& stack, Context context, int level, int character): State(stack, context) {

    mText.setFont(context.fonts->get(Fonts::Main));
    mText.setString(toString(level) + " " + toString(character));
    mText.setCharacterSize(50);
    mText.setFillColor(sf::Color(0, 0, 0, 255));
    mText.setOrigin(mText.getLocalBounds().width / 2.0f, mText.getLocalBounds().height / 2.0f);
    mText.setPosition(640, 100);

    PauseButton.setTexture(context.textures->get(Textures::TestLevel));
    PauseButton.setTextureRect(sf::IntRect(0, 0, 80, 50));
    PauseButton.setPosition(0, 590);



}

void GameState::draw() {
    sf::RenderWindow& window = *getContext().window;
    
    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(255, 255, 255));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));
    backgroundShape.setPosition(0, 0);

    window.draw(backgroundShape);
    window.draw(mText);
    window.draw(PauseButton);
}

bool GameState::update(sf::Time deltatime)
{
	return false;
}

bool GameState::handleEvent(const sf::Event& event)
{

    if(event.type == sf::Event::MouseButtonPressed) {
        if(event.mouseButton.button == sf::Mouse::Left) {
            if(PauseButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                requestStackPush(States::Pause);
            }
        }
    }
	return false;
}