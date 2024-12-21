#include <PauseState.hpp>
#include <Button.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <SFML/System/Time.hpp>


PauseState::PauseState(StateStack& stack, Context context): State(stack, context) {

    ContinueButton.setTexture(context.textures->get(Textures::TestLevel));
    ContinueButton.setTextureRect(sf::IntRect(0, 0, 80, 50));
    ContinueButton.setPosition(0, 590);



}

void PauseState::draw() {
    sf::RenderWindow& window = *getContext().window;
    
    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 128));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));
    backgroundShape.setPosition(0, 0);

    window.draw(backgroundShape);

    sf::RectangleShape PauseShape;
    PauseShape.setFillColor(sf::Color(255, 255, 255, 255));
    PauseShape.setSize(sf::Vector2f(200, 200));
    PauseShape.setPosition(540, 220);

    window.draw(PauseShape);

    window.draw(ContinueButton);

}

bool PauseState::update(sf::Time deltatime)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{

    if(event.type == sf::Event::MouseButtonPressed) {
        if(event.mouseButton.button == sf::Mouse::Left) {
            if(ContinueButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                requestStackPop();
                requestStackPush(States::Waiting);
            }
        }
    }
	return false;
}