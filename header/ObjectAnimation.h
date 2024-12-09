#pragma once
#include <SFML/Graphics.hpp>

class ObjectAnimation
{
public:
	ObjectAnimation(sf::Sprite& sprite, float frameTime) : sprite(sprite), frameTime(frameTime), currentFrame(0), elapsedTime(0) {}
	virtual void addFrame(const sf::IntRect& frame) = 0;
	virtual void update(float deltatime, bool loop = true) = 0;
	virtual void applyToSprite(sf::Sprite& sprite) = 0;
	virtual bool isFinished() const = 0;
protected:
	std::vector<sf::IntRect> frames;  // Frames of the animation
	sf::Sprite& sprite;               // Sprite to animate
	float frameTime;                  // Time for each frame
	float elapsedTime;                // Time tracker for switching frames
	unsigned int currentFrame;// Index of the current frame
	bool finished = false;
};