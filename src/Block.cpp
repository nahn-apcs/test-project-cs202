#include "Block.h"


Block::Block(const sf::Texture& texture) : isSolid(false), isAnimated(false), isMoving(false) {
  sprite.setTexture(texture);
  sprite.setTextureRect(sf::IntRect(0, 0, 32, 32)); 
  item = "";
  movement = nullptr;
  animation = nullptr;
  state = nullptr;

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
  if (isMoving && movement) {
    movement->move(sprite, deltatime, mapData, tileSize);
  }

  if (isAnimated && animation) {
    animation->update(deltatime);
    animation->applyToSprite(sprite, true);
  }
}

void Block::draw(sf::RenderWindow& window) {
  window.draw(sprite);
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

void Block::ontouch()
{
  if (state)
    state->ontouch(*this);
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

sf::Sprite& Block::getSprite()
{
  return sprite;
}
