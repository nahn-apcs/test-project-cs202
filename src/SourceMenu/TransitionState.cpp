#include <TransitionState.hpp>
#include <Button.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <SFML/System/Time.hpp>


TransitionState::TransitionState(StateStack& stack, Context context, std::function<void()> onFinish)
    : State(stack, context)
    , mAlpha(0)  // Bắt đầu với alpha = 0 (bình thường)
    , mDuration(sf::seconds(0.7f))  // Mỗi giai đoạn kéo dài 0.5 giây
    , mElapsed(sf::Time::Zero)
    , mOnFinish(onFinish) {
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

    if (mElapsed < mDuration) {
        // Tăng alpha dựa trên thời gian trôi qua
        float progress = mElapsed.asSeconds() / mDuration.asSeconds();
        mAlpha = 255 * progress;  // Alpha tăng dần từ 0 -> 255
        mOverlay.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(mAlpha)));
    }
    else {
        if (mOnFinish)
            mOnFinish();
    }

    return false;
}

bool TransitionState::handleEvent(const sf::Event& event)
{
    return false;
}