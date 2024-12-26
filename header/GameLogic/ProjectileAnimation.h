#pragma once
#include <SFML/Graphics.hpp>
#include "ObjectAnimation.h"

class ProjectileAnimation : public ObjectAnimation {
	public:
	ProjectileAnimation(sf::Sprite& sprite, float frameTime, bool mr);
	void addFrame(const sf::IntRect& frame);
	void update(float deltatime, bool loop = true, bool b = true);
	void applyToSprite(sf::Sprite& sprite, bool b);
	bool isFinished() const;
	private:
		bool moveRight;
};