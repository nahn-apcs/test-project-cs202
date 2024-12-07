#include"Monster.h"


Monster::Monster(sf::Texture& texture) : movementStrategy(nullptr) {
  sprite.setTexture(texture);
}

Monster::~Monster()
{
  delete movementStrategy;
}

void Monster::setMovementStrategy(MovementStrategy* movementStrategy)
{
  this->movementStrategy = movementStrategy;
}

void Monster::move(float deltatime)
{
  movementStrategy->move(sprite, deltatime);
}

void Monster::draw(sf::RenderWindow& window)
{
  window.draw(sprite);
}

void Monster::setPosition(float x, float y)
{
  sprite.setPosition(x, y);
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
  }
  else if (type == "Turtle")
  {
    Monster *turtle = new Turtle(texture);
    turtle->setMovementStrategy(new PatrolMovement());
  }
  else if (type == "Plant") {
    Monster* plant = new Plant(texture);
    plant->setMovementStrategy(new JumpupMovement(100.f, 2.f));
  }
  else
    return nullptr;
}


