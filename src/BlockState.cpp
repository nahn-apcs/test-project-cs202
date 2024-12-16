#include"BlockState.h"

void ActiveState::ontouch(Block& block,
                          std::vector<std::string>& mapData,
                          int tileSize, sf::Texture& texture)
{
  
  if (dynamic_cast<QuestionBlock*>(&block)) {
    if (block.getItem() == "coin") {
      
        Item* coin = ItemFactory::createItem("Coin", texture, { block.getPosition().x, block.getPosition().y - 36 });

        block.setItemObject(coin);
      }
  
    }
    
    //.setState(new InactiveState());
    //block.update(0.1f, mapData, tileSize);
  
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

void InactiveState::ontouch(Block& block,
                            std::vector<std::string>& mapData,
                            int tileSize,
                            sf::Texture& text)
{
// std::cout<<"Inactive state"<<std::endl;
  block.setTextureRect(sf::Rect(32*5, 0, 32, 32));
  block.setSolid(true);
  block.setMoving(true);
  block.setAnimated(false);
  //block.setAnimation(nullptr);
  block.setMovement(nullptr);
}

void DestroyedState::ontouch(Block& block,
                             std::vector<std::string>& mapData,
                             int tileSize,
                             sf::Texture& text)
{
  //destroy block
  block.setTextureRect(sf::Rect(0, 0, 0, 0));
  block.setPosition(-1000, -1000);
}