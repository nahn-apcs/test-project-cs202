#include "Coin.h"
#include <iostream>
Coin::Coin(sf::Texture& texture, int x, int y)
    : collected(false) {
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(9 * 32, 32, 32, 32));
    sf::Sprite coinSprite;
    coinSprite.setTexture(texture);
    animation = new BlockAnimation(coinSprite, 0.3f);
    
    animation->addFrame(sf::IntRect(9 * 32, 32, 32, 32));
    animation->addFrame(sf::IntRect(10 * 32, 32, 32, 32));
    animation->addFrame(sf::IntRect(11 * 32, 32, 32, 32));
    sprite.setPosition(x, y);
}

Coin::~Coin() {
	if (animation) {
		delete animation;
	}
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

void Coin::update(float deltatime) {
	if (animation) {
		animation->update(deltatime);
		animation->applyToSprite(sprite, true);
	}
}

