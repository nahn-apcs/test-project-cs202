#ifndef WINNING_STATE_HPP
#define WINNING_STATE_HPP

#include <SFML/Graphics.hpp>

#include <State.hpp>
#include <Container.hpp>
#include <vector>

class WinningState : public State {

public:
    WinningState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    sf::Sprite mBackgroundSprite;
    sf::Sprite mRestartButton;
    sf::Sprite mBoard;
};

#endif // WINNING_STATE_HPP