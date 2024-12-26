#include "BlockAnimation.h"
#include <iostream>
BlockAnimation::BlockAnimation(sf::Sprite& sprite, float frameTime) : ObjectAnimation(sprite, frameTime)
{
};


void BlockAnimation::addFrame(const sf::IntRect& frame)
{
  frames.push_back(frame);
}

void BlockAnimation::update(float deltatime,bool loop, bool b)
{
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

  sprite.setTextureRect(frames[currentFrame]);
}


void BlockAnimation::applyToSprite(sf::Sprite& sprite, bool b)
{
  sprite.setTextureRect(frames[currentFrame]);
}

bool BlockAnimation::isFinished() const
{
  return finished;
}

