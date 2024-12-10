#include"BlockState.h"

void ActiveState::ontouch(Block& block)
{
  if (dynamic_cast<QuestionBlock*>(&block)) {
    //implement animation
    block.setState(new InactiveState());
  }
  if (dynamic_cast<BrickBlock*>(&block)) {
    //implement animation
    block.setState(new DestroyedState());
  }

  if (dynamic_cast<HiddenBlock*>(&block)) {
    //implement animation
    block.setState(new InactiveState());
  }

  if (dynamic_cast<CoinBlock*>(&block)) {
    //implement animation
    block.setState(new DestroyedState());
  }
}

void InactiveState::ontouch(Block& block)
{
  block.setSolid(true);
  block.setMoving(false);
  block.setAnimated(false);
  block.setAnimation(nullptr);
  block.setMovement(nullptr);
}

void DestroyedState::ontouch(Block& block)
{
  //destroy block
  block.setTextureRect(sf::Rect(0, 0, 0, 0));
  block.setPosition(-1000, -1000);
}