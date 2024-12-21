#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <SFML/Graphics.hpp>

#include <State.hpp>
#include <Container.hpp>
#include <vector>

class GameState : public State {

public:
    GameState(StateStack& stack, Context context, int level, int character = 1);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:

    sf::Text mText;
    sf::Sprite PauseButton;


};

#endif // GAME_STATE_HPP