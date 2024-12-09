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

class JumpupMovement : public MovementStrategy {
private:
  float jumpHeight;              
  float jumpInterval;            
  float elapsedTime;            
  bool isJumping;                
  float initialY;                
  float velocityY;              
  const float gravity = 981.0f;  
public:
  JumpupMovement(float jumpHeight, float jumpInterval);
  void move(sf::Sprite& sprite,
            float deltatime,
            std::vector<std::string>& mapData,
            int tileSize) override;
};


class XYmovement : public MovementStrategy {
private:
  sf::Vector2f velocity;

public:
  XYmovement(sf::Vector2f velocity);
  void move(sf::Sprite& sprite,
            float deltatime,
            std::vector<std::string>& mapData,
            int tileSize) override;
};

class UpDownmovement : public MovementStrategy {
private:
  float initialY;
  float movementrange;
  float speed;

public:
  UpDownmovement(float initailY,float movementrange, float speed);
  void move(sf::Sprite& sprite,
            float deltatime,
            std::vector<std::string>& mapData,
            int tileSize) override;
};



#endif  
