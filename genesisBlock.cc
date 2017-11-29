#include "genesisBlock.h"

bool GenesisBlock::ValidateAux() const {
  return (magic_genesis_number_ == MAGIC_GENESIS_NUMBER);
}

int64_t GenesisBlock::SerializeAux(uint8_t *buf, uint64_t max_size) const {
  if (max_size >= sizeof(magic_genesis_number_)) {
    memcpy(buf, &magic_genesis_number_, sizeof(magic_genesis_number_));
    return sizeof(magic_genesis_number_);
  } else {
    return -1;
  }
}
