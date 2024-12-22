#ifndef TRANSITION_STATE_HPP
#define TRANSITION_STATE_HPP

#include <SFML/Graphics.hpp>

#include <State.hpp>
#include <Container.hpp>
#include <vector>
#include <functional>

class TransitionState : public State {

public:
    enum Phase {
        FadeIn,
        FadeOut,
    };
    TransitionState(StateStack& stack, Context context, std::function<void()> onFinish);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    sf::RectangleShape mOverlay;      // Hình chữ nhật màu trắng
    float mAlpha;                     // Độ trong suốt (255 -> 0)
    sf::Time mDuration;               // Thời gian chuyển đổi
    sf::Time mElapsed;                // Thời gian đã trôi qua
    std::function<void()> mOnFinish;  // Hàm callback khi hoàn thành

};

#endif // TRANSITION_STATE_HPP