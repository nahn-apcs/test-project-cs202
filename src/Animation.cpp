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

void Animation::applyToSprite(sf::Sprite& sprite) {
    //std::cout << "Applying frame " << currentFrame << std::endl;
    sprite.setTexture(frames[currentFrame]);
}
