#include "block.h"

Block::Block(int64_t type) {
  type_ = type;
}

int64_t Block::Serialize(uint8_t *buf, uint64_t max_size) const {
  uint64_t bytes_written = 0;

  if (max_size >= sizeof(type_)) {
    memcpy(buf, &type_, sizeof(type_));
    bytes_written += sizeof(type_);
  } else {
    return -1;
  }

  int64_t payload_size = SerializeAux(buf + bytes_written,
                                      max_size - bytes_written);
  if (payload_size < 0) {
    return -1;
  } else {
    bytes_written += payload_size;
  }

  uint8_t hash[SHA256_DIGEST_LENGTH];
	ComputeHash(buf, bytes_written, hash);
  if (max_size - bytes_written < sizeof(hash)) {
		return -1;
	} else {
		memcpy(buf + bytes_written, &hash, sizeof(hash));
    bytes_written += sizeof(hash);
	}

	return bytes_written;
}

bool Block::Validate() const {
  // First have the contents validate themselves
  if (!ValidateAux()) {
    return false;
  }

  // Next serialize the contents and confirm the sha256 hash
  uint8_t validation_buffer[MAX_BLOCK_SIZE];
  int64_t len = Serialize(validation_buffer, sizeof(validation_buffer));
  if (len < 0) {
    cerr << RED << "Not enought room to serialize/validate a block.  "
         << "Increase MAX_BLOCK_SIZE to make more room." << RESET << endl;
    return false;
  }
  uint8_t hash[SHA256_DIGEST_LENGTH];
  ComputeHash(validation_buffer, len - SHA256_DIGEST_LENGTH, hash);
  if (memcmp(hash, validation_buffer + len - SHA256_DIGEST_LENGTH,
             SHA256_DIGEST_LENGTH) != 0) {
    return false;
  }
  
  return true;
}

void Block::ComputeHash(uint8_t* buf, uint64_t len, uint8_t* hash) const {
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, buf, len);
  SHA256_Final(hash, &sha256);
}
