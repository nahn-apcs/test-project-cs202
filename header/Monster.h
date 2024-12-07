#ifndef ENTITY_H
#define ENTITY_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<memory>
#include "MovementStrategy.h"

class Monster {
protected:
  sf::Sprite sprite;
  MovementStrategy* movementStrategy;

public:
  Monster(sf::Texture& texture);
  virtual ~Monster();
  virtual void setMovementStrategy(MovementStrategy* movementStrategy);
  virtual void move(float deltatime);
  virtual void draw(sf::RenderWindow& window);
  void setPosition(float x, float y);

};

class Goomba : public Monster {
public:
  Goomba(sf::Texture& texture);
  ~Goomba();
};

class Turtle : public Monster {
public:
  Turtle(sf::Texture& texture);
  ~Turtle();
};

class Plant : public Monster {
public:
	Plant(sf::Texture& texture);
	~Plant();
};

class MonsterFactory {
public:
	static Monster* createMonster(const std::string& type, sf::Texture& texture);
};


#endif  // !ENTITY_H
