#pragma once
#include <SFML/Graphics.hpp>
#include "ObjectAnimation.h"

class CoinAnimation : public ObjectAnimation {
	public:
	CoinAnimation(sf::Sprite& sprite, float frameTime);
	void addFrame(const sf::IntRect& frame);
	void update(float deltatime, bool loop = true, bool b = true);
	void applyToSprite(sf::Sprite& sprite, bool b);
	bool isFinished() const;
};