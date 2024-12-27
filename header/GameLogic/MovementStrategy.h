#ifndef MOVEMENTSTRATEGY_H
#define MOVEMENTSTRATEGY_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<memory>

class MovementStrategy {

public:
  virtual void move(sf::Sprite& sprite,float deltatime,std::vector<std::string>& mapData,
                    int tileSize) = 0;
  bool moveRight(){return (direction >0) ;}
protected:
    float direction = -1.0f;
};

class PatrolMovement : public MovementStrategy {
	public:
  void move(sf::Sprite& sprite,
            float deltatime,
            std::vector<std::string>& mapData,
            int tileSize) override;


};


class XYmovement : public MovementStrategy {
private:
  sf::Vector2f velocity;
  float movementrange;
  float initialX;

public:
  XYmovement(sf::Vector2f velocity, float movementrange, float initialX);
  void move(sf::Sprite& sprite,
            float deltatime,
            std::vector<std::string>& mapData,
            int tileSize) override;
};

class UpDownmovement : public MovementStrategy {
private:
  sf::Vector2f velocity;
  float movementrange;
  float initialX;

public:
  UpDownmovement(sf::Vector2f velocity, float movementrange, float initialX);
  void move(sf::Sprite& sprite,
            float deltatime,
            std::vector<std::string>& mapData,
            int tileSize) override;
};



#endif  
