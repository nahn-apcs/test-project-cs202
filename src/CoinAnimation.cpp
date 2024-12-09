#include "CoinAnimation.h"

CoinAnimation::CoinAnimation(sf::Sprite& sprite, float frameTime) : ObjectAnimation(sprite, frameTime)
{
};


void CoinAnimation::addFrame(const sf::IntRect& frame)
{
  frames.push_back(frame);
}

void CoinAnimation::update(float deltatime,bool loop, bool b)
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


void CoinAnimation::applyToSprite(sf::Sprite& sprite, bool b)
{
  sprite.setTextureRect(frames[currentFrame]);
}

bool CoinAnimation::isFinished() const
{
  return finished;
}

