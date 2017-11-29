#ifndef GENESISBLOCK_H
#define GENESISBLOCK_H

// TODO: In a real application this would be some kind of
// digital signature, I would imagine.  When/if things are
// working you should upgrade how the Genesis block is
// verified instead of just checking this number.
#define MAGIC_GENESIS_NUMBER 0xFFFF

#include <cstring>
#include "block.h"

using std::memcpy;

class GenesisBlock : public Block {
  public:
    GenesisBlock() : Block(GENESIS),
                     magic_genesis_number_(MAGIC_GENESIS_NUMBER) {};

    int64_t SerializeAux(uint8_t *buf, uint64_t max_size) const;
    bool ValidateAux() const;

  private:
    int64_t magic_genesis_number_;
};

#endif // GENESISBLOCK_H
