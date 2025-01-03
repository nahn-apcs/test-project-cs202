#include "Item.h"

Item::Item(const sf::Texture& texture) {
  sprite.setTexture(texture);
  sprite.setTextureRect(sf::IntRect(0, 0, 32, 32)); 
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
  else if (type == "Peach") {
    Item* powerUp = new PowerUp(texture);
    powerUp->setPosition(position.x, position.y);
    auto animation = new BlockAnimation(powerUp->getSprite(), 0.3f);
    animation->addFrame(sf::IntRect(0, 64, 32, 32));
    animation->addFrame(sf::IntRect(32, 64, 32, 32));
    animation->addFrame(sf::IntRect(64, 64, 32, 32));
    animation->addFrame(sf::IntRect(96, 64, 32, 32));
    powerUp->setAnimation(animation);
    auto movement = new PatrolMovement();
    powerUp->setMovement(movement);
    return powerUp;
    
  }
  return nullptr;
}

bool Item::isCollision(const sf::FloatRect& rect)
{
  sf::FloatRect blockBounds = sprite.getGlobalBounds();
  float dx = rect.left - blockBounds.left;
  float dy = rect.top - blockBounds.top;
  float intersectX =
    std::abs(dx) - (rect.width + blockBounds.width) / 2;
  float intersectY =
    std::abs(dy) - (rect.height + blockBounds.height) / 2;
  return intersectX < 4 && intersectY < 0;
}