#include"Monster.h"


Monster::Monster(sf::Texture& texture) : movementStrategy(nullptr), animation(nullptr), isKilled(false) { 
  sprite.setTexture(texture);
  sprite.setTextureRect(sf::IntRect(0, 0, 32, 32)); 
}

Monster::~Monster()
{
  if (movementStrategy)
    delete movementStrategy;
  if (animation)
    delete animation;
}

void Monster::setMovementStrategy(MovementStrategy* movementStrategy)
{
  this->movementStrategy = movementStrategy;
}

void Monster::update(float deltatime,
                     std::vector<std::string>& mapData,
                     int tileSize)
{
  if (movementStrategy)
    movementStrategy->move(sprite, deltatime,mapData,tileSize);

  if (animation)
    animation->update(deltatime);
}

void Monster::draw(sf::RenderWindow& window)
{
  if (animation)
    animation->applyToSprite(sprite);
  window.draw(sprite);
}

void Monster::setPosition(float x, float y)
{
  sprite.setPosition(x, y);
}

void Monster::setAnimation(MonsterAnimation* ani)
{
  if (animation)
    delete animation;
  animation = ani;
}
Goomba::Goomba(sf::Texture& texture) : Monster(texture)
{
}

Goomba::~Goomba()
{
}

Turtle::Turtle(sf::Texture& texture) : Monster(texture)
{
}

Turtle::~Turtle()
{
}

Plant::Plant(sf::Texture& texture) : Monster(texture)
{
}

Plant::~Plant()
{
}

Monster* MonsterFactory::createMonster(const std::string& type,
                                       sf::Texture& texture)
{
  if (type == "Goomba") {
    Monster* goomba = new Goomba(texture);
    goomba->setMovementStrategy(new PatrolMovement());
    auto animation = new MonsterAnimation(goomba->getSprite(), 0.5f);
    animation->addFrame(sf::IntRect(0, 0, 32, 32));
    animation->addFrame(sf::IntRect(32, 0, 32, 32));
    goomba->setAnimation(animation);
  }
  else if (type == "Turtle")
  {
    Monster *turtle = new Turtle(texture);
    turtle->setMovementStrategy(new PatrolMovement());
    auto animation = new MonsterAnimation(turtle->getSprite(), 0.5f);
    animation->addFrame(sf::IntRect(0, 16, 16, 16));
    animation->addFrame(sf::IntRect(16, 16, 16, 16));
    turtle->setAnimation(animation);

  }
  else if (type == "Plant") {
    Monster* plant = new Plant(texture);
    plant->setMovementStrategy(new JumpupMovement(100.f, 2.f));
    auto animation = new MonsterAnimation(plant->getSprite(), 0.2f);
    animation->addFrame(sf::IntRect(0, 64, 16, 16));
    animation->addFrame(sf::IntRect(16, 64, 16, 16));
    plant->setAnimation(animation);
  }
  else
    return nullptr;
}


