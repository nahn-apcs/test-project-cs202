#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>
#include "MovementStrategy.h"
#include "BlockAnimation.h"
#include "BlockState.h"

class BlockState;

class Block {
private:
  sf::Sprite sprite;
  BlockAnimation* animation;
  MovementStrategy* movement;
  BlockState* state;
  bool isSolid;
  bool isAnimated;
  bool isMoving;
  std::string item;
public:
  Block(const sf::Texture& texture);
  ~Block();
  virtual void update(float deltatime, std::vector<std::string>& mapData, int tileSize);
  virtual void draw(sf::RenderWindow& window);
  sf::FloatRect getBounds() const;
  void setMovement(MovementStrategy* movement);
  void setState(BlockState* state);
  void ontouch();
  bool isSolidBlock() const;
  bool isMovingBlock() const;
  bool isAnimatedBlock() const;
  void setAnimation(BlockAnimation* animation);
  void setMoving(bool isMoving);
  void setSolid(bool isSolid);
  void setAnimated(bool isAnimated);
  void setTextureRect(const sf::IntRect& rect);
  void setPosition(float x, float y);
  sf::Sprite& getSprite();

  virtual void setItem(const std::string& item);
  virtual std::string getItem();
};

class QuestionBlock : public Block {
public:
     QuestionBlock(const sf::Texture& texture);
	 ~QuestionBlock();

};

class BrickBlock : public Block {
public:
  BrickBlock(const sf::Texture& texture);
  ~BrickBlock();
};

class HiddenBlock : public Block {
public:
	HiddenBlock(const sf::Texture& texture);
	~HiddenBlock();

};

class CoinBlock : public Block {
public:
  CoinBlock(sf::Texture& texture);
  ~CoinBlock();
};

class BlockFactory {
public:
	static Block* createBlock(const std::string& type, sf::Texture& texture, sf::Vector2i position);
};






#endif  // !BLOCK_H
