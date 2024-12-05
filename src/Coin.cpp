#include "Coin.h"

Coin::Coin(sf::Sprite& texture, int x, int y)
    : collected(false) {
    sprite = texture;
    sprite.setPosition(x, y);
}

void Coin::draw(sf::RenderWindow& window) {
    if (!collected) {
        window.draw(sprite);
    }
}

sf::FloatRect Coin::getBounds() const {
    return sprite.getGlobalBounds();
}

bool Coin::isCollected() const {
    return collected;
}

void Coin::collect() {
    collected = true; // Mark the coin as collected
}
