#pragma once
#include <SFML/Graphics.hpp>

class ObjectAnimation
{
public:
	ObjectAnimation(sf::Sprite& sprite, float frameTime) : sprite(sprite), frameTime(frameTime), currentFrame(0), elapsedTime(0) {}
	virtual void addFrame(const sf::IntRect& frame) = 0;
	virtual void update(float deltatime, bool loop = true, bool b = true) = 0;
	virtual void applyToSprite(sf::Sprite& sprite, bool b) = 0;
	virtual bool isFinished() const = 0;
	sf::IntRect flipFrame(const sf::IntRect& frame) {
		return sf::IntRect(frame.left + frame.width, frame.top, -frame.width, frame.height);
	}
protected:
	std::vector<sf::IntRect> frames;  // Frames of the animation
	sf::Sprite& sprite;               // Sprite to animate
	float frameTime;                  // Time for each frame
	float elapsedTime;                // Time tracker for switching frames
	unsigned int currentFrame;// Index of the current frame
	bool finished = false;
};