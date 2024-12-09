#ifndef MONSTERANIMATION_H
#define MONSTERANIMATIOn_H

#include <SFML/Graphics.hpp>

class MonsterAnimation {
private:
  std::vector<sf::IntRect> frames;  // Frames of the animation
  sf::Sprite& sprite;               // Sprite to animate
  float frameTime;                  // Time for each frame
  float elapsedTime;                // Time tracker for switching frames
  unsigned int currentFrame;// Index of the current frame
  bool finished = false;
public:
  MonsterAnimation(sf::Sprite& sprite, float frameTime);
  void addFrame(const sf::IntRect& frame);
  void update(float deltatime, bool loop=true);
  void applyToSprite(sf::Sprite& sprite);
  bool isFinished() const;
};
#endif  // !MONSTERAL_H
