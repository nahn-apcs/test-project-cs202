#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include "MovementStrategy.h"
#include "ObjectAnimation.h"
#include "BlockAnimation.h"
#include <vector>
#include <string>

class Item {
protected:
  sf::Sprite sprite;
  BlockAnimation* animation;
  MovementStrategy* movement;
  bool isAnimated;
  bool isMoving;
  std::string item;
  bool collected;
 

public:
  Item(const sf::Texture& texture);
  ~Item();
  virtual void update(float deltatime,
                      std::vector<std::string>& mapData,
                      int tileSize);
  virtual void draw(sf::RenderWindow& window);
  void setPosition(float x, float y);
  void setAnimation(BlockAnimation* animation);
  sf::FloatRect getBounds() const;
  void setMovement(MovementStrategy* movement);
  bool isCollected() const;
  void collect();
  sf::Sprite& getSprite();
  bool isCollision(const sf::FloatRect& rect);
  sf::Vector2f getPosition() const { return sprite.getPosition(); }

};

class Coin : public Item {

public:
  Coin(const sf::Texture& texture);
  ~Coin();
};


class PowerUp : public Item {
public:
	PowerUp(const sf::Texture& texture);
	~PowerUp();
};

class ItemFactory {
public:
    static Item* createItem(const std::string& type,  sf::Texture& texture,const sf::Vector2i position);
};


#endif  // !Item_H
