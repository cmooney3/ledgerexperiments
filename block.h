#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <cstring>
#include <stdint.h>
#include "openssl/sha.h"
#include "colors.h"

using std::cerr;
using std::endl;
using std::memcmp;
using std::memcpy;

#define MAX_BLOCK_SIZE 128

#define GENESIS 1
#define TRANSACTION 2
#define ACCOUNT 3

class Block {
  public:
    Block(int64_t type);

    virtual int64_t Serialize(uint8_t *buf, uint64_t max_size) const;
    virtual int64_t SerializeAux(uint8_t *buf, uint64_t max_size) const = 0;

    virtual bool Validate() const;
    virtual bool ValidateAux() const = 0;

		void ComputeHash(uint8_t* buf, uint64_t len, uint8_t* hash) const;

    int64_t type_;
};

#endif // BLOCK_H
