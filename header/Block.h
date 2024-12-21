#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>
#include "MovementStrategy.h"
#include "BlockAnimation.h"
#include "BlockState.h"
#include "Item.h"
#include <vector>

class BlockState;

class Block {
protected:
  sf::Sprite sprite;
  BlockAnimation* animation;
  MovementStrategy* movement;
  BlockState* state;
  float initY;
  float velocityY;
  bool isSolid;
  bool isAnimated;
  bool isMoving;
  bool isTouched = false;
  float coinTime = 0.5f;
  std::string item;
  Item* itemObject;
  sf::Texture texture;
  bool isDestroyed = false;

public:
  Block(const sf::Texture& texture);
  ~Block();
  virtual void update(float deltatime, std::vector<std::string>& mapData, int tileSize);
  virtual void draw(sf::RenderWindow& window);
  sf::FloatRect getBounds() const;
  void setMovement(MovementStrategy* movement);
  void setState(BlockState* state);
  void ontouch(std::vector<std::string>& mapData, int tileSize);
  bool isSolidBlock() const;
  bool isMovingBlock() const;
  bool isAnimatedBlock() const;
  void setAnimation(BlockAnimation* animation);
  void setMoving(bool isMoving);
  void setSolid(bool isSolid);
  void setAnimated(bool isAnimated);
  void setTextureRect(const sf::IntRect& rect);
  void setPosition(float x, float y);
  void onTouch2(std::vector<std::string>& mapData,
                int tileSize,
                sf::Texture& texture);
  void setItemObject(Item* item);
  void setDestroyed(bool isDestroyed);
  bool getIsTouched();
  void move(float x, float y);
  void setInitY(float y);
  Item* getItemObject();
  float getCoinTime();
  sf::Sprite getSprite();


  virtual void setItem(const std::string& item);
  virtual std::string getItem();
  sf::Vector2i	getPosition();
  bool isCollission(const sf::FloatRect& playerbounds) const;
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

class WaterBlock : public Block {
public:
	WaterBlock(const sf::Texture& texture);
	~WaterBlock();

};

class DestroyedBlock : public Block {
public:
  DestroyedBlock(const sf::Texture& texture);
  ~DestroyedBlock();

};

class BlockFactory {
public:
	static Block* createBlock(const std::string& type, sf::Texture& texture, sf::Vector2i position);
};






#endif  // !BLOCK_H
