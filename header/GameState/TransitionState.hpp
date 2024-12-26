#ifndef TRANSITION_STATE_HPP
#define TRANSITION_STATE_HPP

#include <SFML/Graphics.hpp>

#include <State.hpp>
#include <Container.hpp>
#include <vector>

class TransitionState : public State {

public:
    enum Type {
        Menu,
        Game,
        Winning,
    };
    TransitionState(StateStack& stack, Context context, Type type, int cnt = 1);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    sf::RectangleShape mOverlay;      // Hình chữ nhật màu trắng
    float mAlpha;                     // Độ trong suốt (255 -> 0)
    sf::Time mElapsed;                // Thời gian đã trôi qua
    Type mType;
    int mCntPop;

};

#endif // TRANSITION_STATE_HPP