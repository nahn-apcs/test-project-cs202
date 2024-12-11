#pragma once

#include <SFML/Graphics.hpp>
#include "ProjectileAnimation.h"

ProjectileAnimation::ProjectileAnimation(sf::Sprite& sprite, float frameTime, bool mr) : ObjectAnimation(sprite, frameTime) {
	moveRight = true;
}

void ProjectileAnimation::update(float deltatime, bool loop, bool b) {
	if (finished)
		return;
	elapsedTime += deltatime;
	if (elapsedTime >= frameTime) {
		elapsedTime -= frameTime;
		currentFrame++;
		if (currentFrame >= frames.size()) {
			if (loop) {
				currentFrame = 0;
			}
			else {
				currentFrame = frames.size() - 1;
				finished = true;
			}
		}
	}
	applyToSprite(sprite, b);
}

void ProjectileAnimation::applyToSprite(sf::Sprite& sprite, bool b) {
	if (moveRight) {
		sprite.setTextureRect(flipFrame(frames[currentFrame]));
	}
	else {
		sprite.setTextureRect(frames[currentFrame]);
	}
}

void ProjectileAnimation::addFrame(const sf::IntRect& frame) {
	frames.push_back(frame);
}

bool ProjectileAnimation::isFinished() const {
	return finished;
}

