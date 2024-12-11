#include "Animation.h"
#include <iostream>

Animation::Animation(const std::vector<sf::Texture>& frames, float switchTime)
    : frames(frames), switchTime(switchTime), totalTime(0), currentFrame(0) {
    if (!frames.empty()) {
		w = frames[0].getSize().x;
		h = frames[0].getSize().y;
	}
	else {
		w = 0;
		h = 0;
	}
}

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
        sprite.setTextureRect(sf::IntRect(w, 0, -w, h));


    }
    else {
        sprite.setTextureRect(sf::IntRect(0, 0, w, h));

    }
}

