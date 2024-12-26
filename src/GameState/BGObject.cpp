#include <BGObject.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cassert>

BGObject::BGObject(const std::vector<sf::Sprite>& objects, const std::vector<float>& speeds)
    : mObjects(objects), mSpeeds(speeds) {
    assert(mObjects.size() == mSpeeds.size()); // Đảm bảo số lượng đối tượng và tốc độ tương ứng
}

void BGObject::addObject(const sf::Sprite& sprite, float speed) {
    mObjects.push_back(sprite);
    mSpeeds.push_back(speed);
}

void BGObject::updateCurrent(sf::Time dt, CommandQueue&) {
    for (std::size_t i = 0; i < mObjects.size(); ++i) {
        mObjects[i].move(-mSpeeds[i] * dt.asSeconds(), 0); // Di chuyển đối tượng theo tốc độ

        // Đặt lại vị trí nếu đối tượng ra khỏi màn hình
        if (mObjects[i].getPosition().x + mObjects[i].getLocalBounds().width < 0) {
            mObjects[i].setPosition(1280, mObjects[i].getPosition().y);
        }
    }
}

void BGObject::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& object : mObjects) {
        target.draw(object, states);
    }
}
