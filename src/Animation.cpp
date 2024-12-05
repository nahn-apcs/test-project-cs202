#include "Animation.h"
#include <iostream>

Animation::Animation(const std::vector<sf::Texture>& frames, float switchTime)
    : frames(frames), switchTime(switchTime), totalTime(0), currentFrame(0) {}

void Animation::update(float deltaTime) {
    totalTime += deltaTime;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentFrame = (currentFrame + 1) % frames.size();  // Loop through the frames
    }
}

void Animation::applyToSprite(sf::Sprite& sprite, bool faceRight) {
    // Apply the current frame texture
    sprite.setTexture(frames[currentFrame]);

    // Flip sprite horizontally if not facing right
    if (!faceRight) {
        sprite.setTextureRect(sf::IntRect(64, 0, -64, 64));


    }
    else {
        sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

    }
}

