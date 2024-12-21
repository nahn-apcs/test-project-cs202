#ifndef WAITING_STATE_HPP
#define WAITING_STATE_HPP

#include <SFML/Graphics.hpp>

#include <State.hpp>
#include <Container.hpp>
#include <vector>

class WaitingState : public State {

public:
    WaitingState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    sf::Text mText;
    double mTime = 3.0;

};

#endif // WAITING_STATE_HPP