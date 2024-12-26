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

sf::FloatRect Monster::getBounds()
{
  return sprite.getGlobalBounds();
}

void Monster::drawBounds(sf::RenderWindow& window)
{
  sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(getBounds().width, getBounds().height));
  rect.setPosition(getBounds().getPosition());
  rect.setFillColor(sf::Color::Transparent);
  rect.setOutlineColor(sf::Color::Red);
  rect.setOutlineThickness(1.f);
  window.draw(rect);
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
sf::FloatRect Goomba::getBounds()
{
    sf::FloatRect temp = sprite.getGlobalBounds();
    temp.left += temp.width / 4;
    temp.width -= temp.width / 4;
    return temp;
}

sf::FloatRect Bee::getBounds()
{
  sf::FloatRect temp = sprite.getGlobalBounds();
  temp.left += temp.width / 4;
  temp.width -= temp.width / 2;
  temp.top += temp.height / 4;
  temp.height -= temp.height / 2;
  return temp;
}

Bee::Bee(sf::Texture& texture) : Monster(texture)
{
}

Bee::~Bee()
{
}

bee::bee(sf::Texture& texture) : Monster(texture)
{
}

bee::~bee()
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
    return goomba;
    
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
    return bee;

  }
  else if (type == "bee") {
    Monster* be = new bee(texture);
    be->setPosition(position.x, position.y);
    be->setMovementStrategy(
      new UpDownmovement({ 50.0f, 50.0f }, 200.0f, position.x));
    auto animation = new MonsterAnimation(be->getSprite(), 0.5f);
    animation->addFrame(sf::IntRect(0, 96, 64, 64));
    animation->addFrame(sf::IntRect(64, 96, 64, 64));
    animation->addFrame(sf::IntRect(128, 96, 64, 64));
    animation->addFrame(sf::IntRect(192, 96, 64, 64));
    be->setAnimation(animation);
    return be;
  }
  else
    return nullptr;
}

void Monster::kill(bool isKilled, const Monster* monster)
{
  if (isKilled) {
    if (animation) {
      delete animation;
    }
    animation = new MonsterAnimation(sprite, 0.15f);

    if (dynamic_cast<const Goomba*>(monster)) {
      animation->addFrame(sf::IntRect(384, 0, 48, 32));
      animation->addFrame(sf::IntRect(432, 0, 48, 32));
      animation->addFrame(sf::IntRect(480, 0, 48, 32));
      animation->addFrame(sf::IntRect(528, 0, 48, 32));
     

    }
    else if (dynamic_cast<const Bee*>(monster)) {
      animation->addFrame(sf::IntRect(384, 96, 64, 64));
      animation->addFrame(sf::IntRect(448, 96, 64, 64));
      animation->addFrame(sf::IntRect(512, 96, 64, 64));
      animation->addFrame(sf::IntRect(576, 96, 64, 64));
     
    }
    else if (dynamic_cast<const bee*>(monster)) {
        animation->addFrame(sf::IntRect(384, 96, 64, 64));
        animation->addFrame(sf::IntRect(448, 96, 64, 64));
        animation->addFrame(sf::IntRect(512, 96, 64, 64));
        animation->addFrame(sf::IntRect(576, 96, 64, 64));

    }
   
    this->isKilled = true;
  }
}

bool Monster::isAnimationFinished()
{
  return animation->isFinished();
}
