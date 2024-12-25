#include <TransitionState.hpp>
#include <Button.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <SFML/System/Time.hpp>
#include <LevelManager.hpp>


TransitionState::TransitionState(StateStack& stack, Context context, Type type, int Cnt) : State(stack, context), mAlpha(0), mElapsed(sf::Time::Zero), mType(type), mCntPop(Cnt) {
    // Khởi tạo hình chữ nhật phủ toàn màn hình
    mOverlay.setSize(sf::Vector2f(context.window->getSize()));
    mOverlay.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(mAlpha)));
}

void TransitionState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.draw(mOverlay);
}

bool TransitionState::update(sf::Time deltaTime) {
    mElapsed += deltaTime;

    if (mElapsed.asSeconds() < 0.7f) {
        // Tăng alpha dựa trên thời gian trôi qua
        float progress = mElapsed.asSeconds() / 0.7f;
        mAlpha = 255 * progress;  // Alpha tăng dần từ 0 -> 255
        mOverlay.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(mAlpha)));
    }
    else {
        if (mType == Menu) {
            requestStateClear();
            requestStackPush(States::Menu);
        }
        else if (mType == Game) {
            while (mCntPop > 0) {
                requestStackPop();
                mCntPop--;
            }
            requestStackPush(States::Game);

        }
        else if (mType == Winning) {
            requestStateClear();
            requestStackPush(States::Winning);
        }
    }

    return false;
}

bool TransitionState::handleEvent(const sf::Event& event) {
    return false;
}