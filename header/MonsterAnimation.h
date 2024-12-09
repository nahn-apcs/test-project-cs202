#ifndef MONSTERANIMATION_H
#define MONSTERANIMATIOn_H

#include <SFML/Graphics.hpp>

#include "ObjectAnimation.h"


class MonsterAnimation : public ObjectAnimation {
public:
  MonsterAnimation(sf::Sprite& sprite, float frameTime);
  void addFrame(const sf::IntRect& frame);
  void update(float deltatime, bool loop=true);
  void applyToSprite(sf::Sprite& sprite);
  bool isFinished() const;
  
};
#endif  // !MONSTERAL_H
