#ifndef BLOCKSTATE_H
#define BLOCKSTATE_H

#include"Block.h"

class Block;


class BlockState {
public:
  virtual void ontouch(Block& block,
                       std::vector<std::string>& mapData,
                       int tileSize, sf::Texture& text) = 0;
};
class ActiveState : public BlockState {
  void ontouch(Block& block,
               std::vector<std::string>& mapData,
               int tileSize,
               sf::Texture& text) override;
};

class InactiveState : public BlockState {
  void ontouch(Block& block,
               std::vector<std::string>& mapData,
               int tileSize,
               sf::Texture& text) override;
};

class DestroyedState : public BlockState {
  void ontouch(Block& block,
               std::vector<std::string>& mapData,
               int tileSize,
               sf::Texture& text) override;
};


#endif  // !BLOCKSTATE_H
