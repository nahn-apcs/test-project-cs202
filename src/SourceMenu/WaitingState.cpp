#include <WaitingState.hpp>
#include <Button.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <SFML/System/Time.hpp>


WaitingState::WaitingState(StateStack& stack, Context context) : State(stack, context) {
    mText.setFont(context.fonts->get(Fonts::Main));
    mText.setString("3");
    mText.setCharacterSize(50);
    mText.setFillColor(sf::Color(255, 255, 255, 255));
    mText.setOrigin(mText.getLocalBounds().width / 2.0f, mText.getLocalBounds().height / 2.0f);
    mText.setPosition(640, 300);



}

void WaitingState::draw() {
    sf::RenderWindow& window = *getContext().window;

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 128));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));
    backgroundShape.setPosition(0, 0);

    window.draw(backgroundShape);

    window.draw(mText);

}

bool WaitingState::update(sf::Time deltatime)
{
    mTime -= deltatime.asSeconds();
    if (mTime <= 0) {
        requestStackPop();
    }
    else {
        mText.setString(std::to_string((int)mTime + 1));
    }

    return false;
}

bool WaitingState::handleEvent(const sf::Event& event)
{
    return false;
}