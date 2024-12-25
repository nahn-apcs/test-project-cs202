#include <GuideState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <SFML/System/Time.hpp>

GuideState::GuideState(StateStack& stack, Context context) : State(stack, context), mBackgroundSprite() {
    sf::Texture& texture = context.textures->get(Textures::GuideBG);
    mBackgroundSprite = sf::Sprite(texture);
    mBackgroundSprite.setOrigin(mBackgroundSprite.getLocalBounds().width / 2.0f, mBackgroundSprite.getLocalBounds().height / 2.0f);
    mBackgroundSprite.setPosition(640, 320);

    sf::Texture& closeTexture = context.textures->get(Textures::CloseGuide);
    mCloseButton = sf::Sprite(closeTexture);
    mCloseButton.setPosition(900, 88);

    mBackgroundShape.setSize(sf::Vector2f(1280, 640));
    mBackgroundShape.setFillColor(sf::Color(0, 0, 0, 200));
}

void GuideState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackgroundShape);
    window.draw(mBackgroundSprite);
    window.draw(mCloseButton);
}

bool GuideState::update(sf::Time deltatime) {
    return true;
}

bool GuideState::handleEvent(const sf::Event& event) {

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (mCloseButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                requestStackPop();
            }
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            requestStackPop();
        }
    }

    return false;
}
