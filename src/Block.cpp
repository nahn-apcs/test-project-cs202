#include "Block.h"


Block::Block(const sf::Texture& texture) : isSolid(false), isAnimated(false), isMoving(false) {
  sprite.setTexture(texture);
  sprite.setTextureRect(sf::IntRect(0, 0, 32, 32)); 
  item = "";
  movement = nullptr;
  animation = nullptr;
  state = nullptr;
  itemObject = nullptr;
  velocityY = 0;
  coinTime = 0.5f;
  this->texture = texture;
}

Block::~Block()
{
  if (animation) {
    delete animation;
  }
  if (movement) {
    delete movement;
  }
  if (state) {
    delete state;
  }
}

void Block::update(float deltatime, std::vector<std::string>& mapData, int tileSize)
{
  if (isTouched)
  {
 

    if (itemObject) {
      itemObject->update(deltatime, mapData, tileSize);
      if (coinTime < 0.01f) {
        itemObject->collect();
      }
    }
    if (item == "coin") {
      coinTime -= deltatime;
     
    }
    sprite.move(0, velocityY * deltatime);
    velocityY += 10000.f * deltatime;
    if (sprite.getPosition().y >= initY) {
      sprite.setPosition(sprite.getPosition().x, initY);
      velocityY = 0;
      sprite.setTextureRect(sf::IntRect(5 * 32, 0, 32, 32));
      return;
    }
    return;
  } 
  if (isMoving && movement) {
    movement->move(sprite, deltatime, mapData, tileSize);
  }

  if (isAnimated && animation) {
    animation->update(deltatime);
    animation->applyToSprite(sprite, true);
  }
  
}

void Block::move(float x, float y)
{
  sprite.move(x, y);
}

void Block::draw(sf::RenderWindow& window) {
  window.draw(sprite);
  if (isTouched && coinTime > 0.01f) {
    if (itemObject == nullptr) return;
    itemObject->draw(window);
  }
}

sf::FloatRect Block::getBounds() const {
  return sprite.getGlobalBounds();
}

void Block::setMovement(MovementStrategy* movement)
{
  this->movement = movement;
}

void Block::setState(BlockState* state)
{
  this->state = state;
}

void Block::ontouch(std::vector<std::string>& mapData, int tileSize)
{
  if (state) {
    state->ontouch(*this, mapData, tileSize, texture);
    isTouched = true;
  }
}

bool Block::isSolidBlock() const
{
  return isSolid;
}

bool Block::isMovingBlock() const
{
  return isMoving;
}

bool Block::isAnimatedBlock() const
{
  return isAnimated;
}

void Block::setAnimation(BlockAnimation* animation)
{
  this->animation = animation;
}


void Block::setMoving(bool isMoving)
{
  this->isMoving = isMoving;
}

void Block::setSolid(bool isSolid)
{
  this->isSolid = isSolid;
}

void Block::setAnimated(bool isAnimated)
{
  this->isAnimated = isAnimated;
}

void Block::setTextureRect(const sf::IntRect& rect)
{
  sprite.setTextureRect(rect);
}

void Block::setPosition(float x, float y)
{
  sprite.setPosition(x, y);
}

sf::Vector2i	Block::getPosition()
{
  return sf::Vector2i(sprite.getPosition().x, sprite.getPosition().y);
}


bool Block::isCollission(const sf::FloatRect& playerbounds) const
{
   sf::FloatRect blockBounds= sprite.getGlobalBounds();
  float dx = playerbounds.left - blockBounds.left;
   float dy = playerbounds.top - blockBounds.top;
  float intersectX =
    std::abs(dx) - (playerbounds.width + blockBounds.width) / 2;
   float intersectY =
    std::abs(dy) - (playerbounds.height + blockBounds.height) / 2;
   float midX = playerbounds.left + playerbounds.width / 2;
   return intersectX < 0 && intersectY < 0 && midX > blockBounds.left && midX < blockBounds.left + blockBounds.width;
}


QuestionBlock::QuestionBlock(const sf::Texture& texture)
  : Block(texture)
{
}

QuestionBlock::~QuestionBlock()
{
}

BrickBlock::BrickBlock(const sf::Texture& texture)
  : Block(texture)
{
}

BrickBlock::~BrickBlock()
{
}

HiddenBlock::HiddenBlock(const sf::Texture& texture)
  : Block(texture)
{
}

HiddenBlock::~HiddenBlock()
{
}

CoinBlock::CoinBlock(sf::Texture& texture)
  : Block(texture)
{
}

CoinBlock::~CoinBlock()
{
}

Block* BlockFactory::createBlock(const std::string& type, sf::Texture& texture, sf::Vector2i position)
{
  if (type == "question") {
    Block* block = new QuestionBlock(texture);
    block->setPosition(position.x, position.y);
    block->setAnimated(true);
    block->setInitY(position.y);
    auto ani = new BlockAnimation(block->getSprite(), 0.3f);
    ani->addFrame(sf::IntRect(32 * 6, 32, 32, 32));
    ani->addFrame(sf::IntRect(32 * 7, 32, 32, 32));
    ani->addFrame(sf::IntRect(32 * 8, 32, 32, 32));
    block->setAnimation(ani);
    return block;
  }
  else if (type == "brick") {
    BrickBlock* block = new BrickBlock(texture);
    block->setPosition(position.x, position.y);
    block->setTextureRect(sf::IntRect(32, 0, 32,32));
    block->setInitY(position.y);
    return block;
  }
  else if (type == "hidden") {
    HiddenBlock* block = new HiddenBlock(texture);
    block->setPosition(position.x, position.y);
    return block;
  }
  else if (type == "coin") {
    CoinBlock* block = new CoinBlock(texture);
    block->setPosition(position.x, position.y);
    return block;
  }
}

void Block::setItem(const std::string& item)
{
  this->item = item;
}

std::string Block::getItem()
{
  return item;
}

sf::Sprite Block::getSprite()
{
  return sprite;
}


void Block::onTouch2(std::vector<std::string>& mapData, int tileSize, sf::Texture& texture)
{
  if (state) {
    state->ontouch(*this, mapData, tileSize, texture);
  }
  isTouched = true;
  if (item == "coin")
  velocityY = -400.f;
}

bool Block::getIsTouched()
{
  return isTouched;
}

void Block::setInitY(float y)
{
  initY = y;
}

void Block::setItemObject(Item* item)
{
  this->itemObject = item;
}

Item* Block::getItemObject()
{
  return itemObject;
}

float Block::getCoinTime()
{
  return coinTime;
}

