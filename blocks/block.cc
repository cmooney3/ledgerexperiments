#include "block.h"

Block::Block(int64_t type) {
  type_ = type;
}

int64_t Block::Serialize(uint8_t *buf, uint64_t max_size) const {
  int64_t bytes_written = 0;

  // First copy over the block type number
  if (max_size >= sizeof(type_)) {
    memcpy(buf, &type_, sizeof(type_));
    bytes_written += sizeof(type_);
  } else {
    return -1;
  }

  // Note the location of the length value (second field) for now, and
  // and then fill it in later after running the Aux function and before
  // computing the hash.
  int64_t length_position = bytes_written;
  bytes_written += sizeof(bytes_written);  // effectively skipping this field

  // Now call the helper function to serialize the payload
  int64_t payload_size = SerializeAux(buf + bytes_written,
                                      max_size - bytes_written);
  if (payload_size < 0) {
    return -1;
  } else {
    bytes_written += payload_size;
  }

  // Storing the actual length in field 2 now that we've run the Aux function
  // and know how long the block is now.
  memcpy(buf + length_position, &bytes_written, sizeof(bytes_written));

  // Finally compute a sha256 hash of all the preceding data and
  // append it onto the end.
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
