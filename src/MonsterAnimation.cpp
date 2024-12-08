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

void MonsterAnimation::update(float deltatime,bool loop)
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

void MonsterAnimation::applyToSprite(sf::Sprite& sprite)
{
  sprite.setTextureRect(frames[currentFrame]);
}

bool MonsterAnimation::isFinished() const
{
  return finished;
}

