#include"Monster.h"


Monster::Monster(sf::Texture& texture) : movementStrategy(nullptr), animation(nullptr), isKilled(false) { 
  sprite.setTexture(texture);
  sprite.setTextureRect(sf::IntRect(0, 0, 32, 32)); 
  //moveRight = true;
  //moveOffset = 100.f;
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
  if (isKilled && animation) {
    animation->update(deltatime, false);  // Play death animation once
    if (animation->isFinished()) {
      sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));// Hide sprite after animation
      sprite.setPosition(-1000, -1000);  // Move sprite off screen
       
    }
  }
  else if (movementStrategy) {
    movementStrategy->move(sprite, deltatime, mapData, tileSize);
  }

  if (!isKilled && animation) {
    animation->update(deltatime);
  }
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
    animation->addFrame(sf::IntRect(64, 0, 32, 32));
    animation->addFrame(sf::IntRect(96, 0, 32, 32));
    goomba->setAnimation(animation);
  }
  else if (type == "Turtle")
  {
    Monster *turtle = new Turtle(texture);
    turtle->setMovementStrategy(new PatrolMovement());
    auto animation = new MonsterAnimation(turtle->getSprite(), 0.5f);
    animation->addFrame(sf::IntRect(0, 32, 32, 32));
    animation->addFrame(sf::IntRect(32, 32, 32, 32));
    animation->addFrame(sf::IntRect(64, 32, 32, 32));
    animation->addFrame(sf::IntRect(96, 32, 32, 32));
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

void Monster::kill(bool isKilled, const std::string& type)
{
  if (isKilled) {
    if (animation) {
      delete animation;
    }
    animation = new MonsterAnimation(sprite, 0.1f);

    if (type == "M") {
      animation->addFrame(sf::IntRect(0, 32, 32, 32));  // Example death frames
      animation->addFrame(sf::IntRect(32, 32, 32, 32));
    }
    else if (type == "T") {
      animation->addFrame(sf::IntRect(0, 32, 32, 32));
      animation->addFrame(sf::IntRect(32, 32, 32, 32));
    }
    else if (type == "Plant") {
      animation->addFrame(sf::IntRect(0, 160, 32, 32));
      animation->addFrame(sf::IntRect(32, 160, 32, 32));
    }

    this->isKilled = true;
  }
}

bool Monster::isAnimationFinished()
{
  return animation->isFinished();
}
