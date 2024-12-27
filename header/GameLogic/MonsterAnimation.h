#ifndef MONSTERANIMATION_H
#define MONSTERANIMATION_H

#include <SFML/Graphics.hpp>
#include "ObjectAnimation.h"

class MonsterAnimation: public ObjectAnimation {

public:
  MonsterAnimation(sf::Sprite& sprite, float frameTime);
  void addFrame(const sf::IntRect& frame);
  void update(float deltatime, bool loop=true, bool b = true);
  void applyToSprite(sf::Sprite& sprite, bool moveRight);
  bool isFinished() const;
};
#endif  // !MONSTERAL_H
