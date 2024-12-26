#ifndef ENTITY_H
#define ENTITY_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<memory>
#include "MovementStrategy.h"
#include "MonsterAnimation.h"

class Monster {
protected:
  sf::Sprite sprite;
  MovementStrategy* movementStrategy;
  MonsterAnimation* animation;
  bool isKilled;


public:
  Monster(sf::Texture& texture);
  virtual ~Monster();
  virtual void setMovementStrategy(MovementStrategy* movementStrategy);
  virtual void update(float deltatime,
                      std::vector<std::string>& mapData,
                      int tileSize);
  virtual void draw(sf::RenderWindow& window);
  void setPosition(float x, float y);
  void setAnimation(MonsterAnimation* ani);
  virtual void kill(bool isKilled, const Monster* monster);
  virtual sf::FloatRect getBounds();
  void drawBounds(sf::RenderWindow& window);

  sf::Sprite& getSprite() { return sprite; }
  bool getIsKilled() { return isKilled; }
  bool isAnimationFinished();
  sf::Vector2f getPosition(){ return sprite.getPosition(); }
};

class Goomba : public Monster {
public:
  Goomba(sf::Texture& texture);
  ~Goomba();
  sf::FloatRect getBounds();
};

class Bee : public Monster {
public:
  Bee(sf::Texture& texture);
  ~Bee();
  sf::FloatRect getBounds();
};

class bee : public Monster {
public:
	bee(sf::Texture& texture);
	~bee();
};

class MonsterFactory {
public:
	static Monster* createMonster(const std::string& type, sf::Texture& texture, sf::Vector2i position);
};


#endif  // !ENTITY_H
