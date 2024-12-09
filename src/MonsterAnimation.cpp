#include "MonsterAnimation.h"
#include "ObjectAnimation.h"

MonsterAnimation::MonsterAnimation(sf::Sprite& sprite, float frameTime) : ObjectAnimation(sprite, frameTime)
{};

void MonsterAnimation::addFrame(const sf::IntRect& frame)
{
  frames.push_back(frame);
}

void MonsterAnimation::update(float deltatime,bool loop, bool faceRight)
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

void MonsterAnimation::applyToSprite(sf::Sprite& sprite, bool faceRight)
{
  //sprite.setTextureRect(frames[currentFrame]);
  // Flip sprite horizontally if not facing right
    if (faceRight) {
      sprite.setTextureRect(flipFrame(frames[currentFrame]));
  }
  else {
      sprite.setTextureRect(frames[currentFrame]);
  }

}

bool MonsterAnimation::isFinished() const
{
  return finished;
}

