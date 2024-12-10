#ifndef BLOCKSTATE_H
#define BLOCKSTATE_H

#include"Block.h"

class Block;


class BlockState {
public:
  virtual void ontouch(Block& block) = 0;
};
class ActiveState : public BlockState {
  void ontouch(Block& block) override;
};

class InactiveState : public BlockState {
  void ontouch(Block& block) override;
};

class DestroyedState : public BlockState {
  void ontouch(Block& block) override;
};


#endif  // !BLOCKSTATE_H
