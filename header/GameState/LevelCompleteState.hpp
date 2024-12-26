#ifndef LEVEL_COMPLETE_STATE_HPP
#define LEVEL_COMPLETE_STATE_HPP

#include <SFML/Graphics.hpp>

#include <State.hpp>
#include <Container.hpp>
#include <vector>

class LevelCompleteState : public State {

public:
    LevelCompleteState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    sf::Sprite mBackgroundSprite;
    sf::Sprite mBackButton;
    sf::Sprite mNextButton;
};

#endif // LEVEL_COMPLETE_STATE_HPP