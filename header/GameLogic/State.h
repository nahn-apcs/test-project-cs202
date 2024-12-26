#pragma once
#include <SFML/Graphics.hpp>

class State {
private:
    sf::Font font;
public:
    virtual ~State() {}

    // Virtual functions for handling events, updating, and rendering
    virtual void handleInput(sf::RenderWindow& window) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    // Optional: For transitioning between states
    virtual void onEnter() = 0;
    virtual void onExit() = 0;
};
