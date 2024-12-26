#ifndef GAME_OVER_STATE_HPP
#define GAME_OVER_STATE_HPP

#include <SFML/Graphics.hpp>

#include <State.hpp>
#include <Container.hpp>
#include <vector>

class GameOverState : public State {

public:
    GameOverState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    sf::RectangleShape mBackground;
    sf::Sprite mBoard;
    sf::Sprite mRestartButton;
    sf::Sprite mMenuButton;
};

#endif // GAME_OVER_STATE_HPP