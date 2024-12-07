#include "MonsterAnimation.h"


MonsterAnimation::MonsterAnimation(sf::Sprite& sprite, float frameTime)
  : sprite(sprite)
  , frameTime(frameTime)
  , elapsedTime(0)
  , currentFrame(0)
{
}

void MonsterAnimation::addFrame(const sf::IntRect& frame)
{
  frames.push_back(frame);
}

void MonsterAnimation::update(float deltatime)
{
  elapsedTime += deltatime;

  if (elapsedTime >= frameTime) {
    elapsedTime -= frameTime;
    currentFrame = (currentFrame + 1) % frames.size();
  }

  sprite.setTextureRect(frames[currentFrame]);
}

void MonsterAnimation::applyToSprite(sf::Sprite& sprite)
{
  sprite.setTextureRect(frames[currentFrame]);
}


