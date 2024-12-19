#ifndef GUIDE_STATE_HPP
#define GUIDE_STATE_HPP

#include <SFML/Graphics.hpp>

#include <State.hpp>
#include <Container.hpp>
#include <vector>

class GuideState : public State {

public:
    GuideState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    sf::Sprite mBackgroundSprite;
    sf::Sprite mCloseButton;
    sf::RectangleShape mBackgroundShape;
};

#endif // GUIDE_STATE_HPP