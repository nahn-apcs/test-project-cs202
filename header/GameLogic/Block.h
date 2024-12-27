#pragma once

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
  BlockState* state;
  float initY;
  float velocityY;
  bool isSolid;
  bool isAnimated;
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
  void setState(BlockState* state);
  void ontouch(std::vector<std::string>& mapData, int tileSize);
  bool isSolidBlock() const;
  bool isAnimatedBlock() const;
  void setAnimation(BlockAnimation* animation);
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
  bool getIsDestroyed() { return isDestroyed; }
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

class FlagBlock : public Block {
public:
	FlagBlock(const sf::Texture& texture);
	~FlagBlock();
};

class BlockFactory {
public:
	static Block* createBlock(const std::string& type, sf::Texture& texture, sf::Vector2i position);
};







