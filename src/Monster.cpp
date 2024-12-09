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
    animation->update(deltatime, false, movementStrategy->moveRight());  // Play death animation once
    if (animation->isFinished()) {
      sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));// Hide sprite after animation
      sprite.setPosition(-1000, -1000);  // Move sprite off screen
       
    }
  }
  else if (movementStrategy) {
    movementStrategy->move(sprite, deltatime, mapData, tileSize);
  }

  if (!isKilled && animation) {
    animation->update(deltatime, true, movementStrategy->moveRight());
  }
}

void Monster::draw(sf::RenderWindow& window)
{
    if (animation) {
        animation->applyToSprite(sprite, movementStrategy->moveRight());
        window.draw(sprite);
    }
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

Bee::Bee(sf::Texture& texture) : Monster(texture)
{
}

Bee::~Bee()
{
}

Plant::Plant(sf::Texture& texture) : Monster(texture)
{
}

Plant::~Plant()
{
}

Monster* MonsterFactory::createMonster(const std::string& type,
                                       sf::Texture& texture, sf::Vector2i position)
{
  if (type == "Goomba") {
    Monster* goomba = new Goomba(texture);
    goomba->setPosition(position.x, position.y);
    goomba->setMovementStrategy(new PatrolMovement());
    auto animation = new MonsterAnimation(goomba->getSprite(), 0.5f);
    animation->addFrame(sf::IntRect(0, 0, 48, 32));
    animation->addFrame(sf::IntRect(48, 0, 48, 32));
    animation->addFrame(sf::IntRect(96, 0, 48, 32));
    animation->addFrame(sf::IntRect(144, 0, 48, 32));
    animation->addFrame(sf::IntRect(192, 0, 48, 32));
    animation->addFrame(sf::IntRect(240, 0, 48, 32));
    goomba->setAnimation(animation);
    
  }
  else if (type == "Bee")
  {
    Monster *bee = new Bee(texture);
    bee->setPosition(position.x, position.y);
    bee->setMovementStrategy(new XYmovement({ 50.0f, 50.0f }, 200.0f, position.x));
    auto animation = new MonsterAnimation(bee->getSprite(), 0.5f);
    animation->addFrame(sf::IntRect(0, 96, 64, 64));
    animation->addFrame(sf::IntRect(64, 96, 64, 64));
    animation->addFrame(sf::IntRect(128, 96, 64, 64));
    animation->addFrame(sf::IntRect(192, 96, 64, 64));
    bee->setAnimation(animation);
    

  }
  else if (type == "bee") {
    Monster* bee = new Bee(texture);
    bee->setPosition(position.x, position.y);
    bee->setMovementStrategy(
      new UpDownmovement({ 50.0f, 50.0f }, 200.0f, position.x));
    auto animation = new MonsterAnimation(bee->getSprite(), 0.5f);
    animation->addFrame(sf::IntRect(0, 96, 64, 64));
    animation->addFrame(sf::IntRect(64, 96, 64, 64));
    animation->addFrame(sf::IntRect(128, 96, 64, 64));
    animation->addFrame(sf::IntRect(192, 96, 64, 64));
    bee->setAnimation(animation);
    
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
      animation->addFrame(sf::IntRect(0, 32, 48, 32));  // Example death frames
      animation->addFrame(sf::IntRect(48, 32, 32, 32));
    }
    else if (type == "B") {
      animation->addFrame(sf::IntRect(0, 32, 32, 32));
      animation->addFrame(sf::IntRect(32, 32, 32, 32));
    }
    else if (type == "T") {
      animation->addFrame(sf::IntRect(0, 64, 32, 32));
      animation->addFrame(sf::IntRect(32, 64, 32, 32));
    }

    this->isKilled = true;
  }
}

bool Monster::isAnimationFinished()
{
  return animation->isFinished();
}
