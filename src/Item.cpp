#include "Item.h"

Item::Item(const sf::Texture& texture) {
  sprite.setTexture(texture);
  collected = false;
  isAnimated = true;
  isMoving = true;
  animation = nullptr;
  movement = nullptr;
}

Item::~Item()
{
  if (animation) {
    delete animation;
  }
  if (movement) {
    delete movement;
  }
}



void Item::update(float deltatime,
                  std::vector<std::string>& mapData,
                  int tileSize)
{
  if (isMoving && movement) {
    movement->move(sprite, deltatime, mapData, tileSize);
  }

  if (isAnimated && animation) {
    animation->update(deltatime);
    animation->applyToSprite(sprite, true);
  }
}


void Item::draw(sf::RenderWindow& window) {
  if(!collected) window.draw(sprite);
}

void Item::setPosition(float x, float y) {
  sprite.setPosition(x, y);
}

void Item::setAnimation(BlockAnimation* animation)
{
  this->animation = animation;
}


sf::FloatRect Item::getBounds() const {
  return sprite.getGlobalBounds();
}

bool Item::isCollected() const
{
  return collected;
}

void Item::collect()
{
  collected = true;
}

sf::Sprite& Item::getSprite()
{
  return sprite;
}


void Item::setMovement(MovementStrategy* movement)
{
  this->movement = movement;
}


Coin::Coin(const sf::Texture& texture) : Item(texture) {
}

Coin::~Coin()
{
}

Mushroom::Mushroom(const sf::Texture& texture) : Item(texture) {
}

Mushroom::~Mushroom()
{
}

PowerUp::PowerUp(const sf::Texture& texture) : Item(texture) {
}

PowerUp::~PowerUp()
{
}


Item* ItemFactory::createItem(const std::string& type,
                               sf::Texture& texture,const sf::Vector2i position)
{
  if (type == "Coin") {
    Item *coin = new Coin(texture);
    coin->setPosition(position.x, position.y);
    auto animation = new BlockAnimation(coin->getSprite(), 0.3f);
    animation->addFrame(sf::IntRect(9 * 32, 32, 32, 32));
    animation->addFrame(sf::IntRect(10 * 32, 32, 32, 32));
    animation->addFrame(sf::IntRect(11 * 32, 32, 32, 32));
    coin->setAnimation(animation);
    return coin;
  }
  else if (type == "Mushroom") {
    Item* mushroom = new Mushroom(texture);
    mushroom->setPosition(position.x, position.y);
    return mushroom;
  
  }
  else if (type == "PowerUp") {
    Item* powerUp = new PowerUp(texture);
    powerUp->setPosition(position.x, position.y);
    return powerUp;
    
  }
  return nullptr;
}

