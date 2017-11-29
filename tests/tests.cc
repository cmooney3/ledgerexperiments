// This program assumes you have checked out acutest from
// https://github.com/mity/acutest.git
#include "acutest/include/acutest.h"

#include "blocks/genesisBlock.h"

constexpr unsigned int kBigEnoughBufferSize = 1024;
constexpr unsigned int kTooSmallBufferSize = 2;

void TestGenesisBlockCreation() {
  // Very basic check confirms that the block is created without error and
  // that the type_ field indicates correctly that it is a GenesisBlock.
  GenesisBlock g;
  TEST_CHECK_(g.type_ == GENESIS,
              "The Genesis Block type_ field was %d instead of %d",
              g.type_, GENESIS);
}

void TestGenesisBlockValidation() {
  GenesisBlock g;
  TEST_CHECK_(g.Validate(), "The Genesis Block failed to Validate");
}

void TestGenesisBlockSerialization() {
  GenesisBlock g;
  uint8_t buf[kBigEnoughBufferSize];
  memset(buf, 0, sizeof(buf));
  int64_t len;

  // First make sure that when you give it a small buffer it fails.
  len = g.Serialize(buf, kTooSmallBufferSize);
  TEST_CHECK_(len == -1, "Serialization failed to detect insufficient space");

  // Now make sure that when you give it a bigger buffer instead.
  len = g.Serialize(buf, kBigEnoughBufferSize);
  TEST_CHECK_(len >= 0, "Serialization failed despite having a %d-byte buffer",
              kBigEnoughBufferSize);

  // The following checks confirm some sanity in the serialization data:
  // Check that the "type" field is set correctly (first 64-bit int)
  uint64_t type_from_serialization;
  memcpy(&type_from_serialization, buf, sizeof(type_from_serialization));
  TEST_CHECK_(type_from_serialization == g.type_,
              "Unexpected 'type' field in serialized block (%d). Expected %d",
              type_from_serialization, g.type_);

  // Check that the length field is set correctly (second 64-bit int)
  uint64_t len_from_serialization;
  memcpy(&len_from_serialization, buf + sizeof(uint64_t),
         sizeof(len_from_serialization));
  TEST_CHECK_(len_from_serialization > 0,
              "Non-positive 'length' field in the serialized block (%d)",
              len_from_serialization);
  TEST_CHECK_(len_from_serialization <= kBigEnoughBufferSize,
              "The 'length' field in the serialized block is bigger than the "
              "size of the buffer it was written in (%d > %d)",
              len_from_serialization, kBigEnoughBufferSize);
}

TEST_LIST = {
   { "Genesis Block Creation", TestGenesisBlockCreation },
   { "Genesis Block Validation", TestGenesisBlockValidation },
   { "Genesis Block Serialization", TestGenesisBlockSerialization },
   { 0 }
};




//void Tester::PrintBuffer(uint8_t *buf, int64_t len) const {
//  cout << "buf = \t0x0000\t[";
//  for (int i = 0; i < len; i++) {
//    cout << std::uppercase << std::setw(2) << std::setfill('0') << std::hex << (int)buf[i];
//    if (i == len - 1) {
//      cout << "]";
//    } else if (i > 0 && i % 8 == 7) {
//      cout << endl << "\t0x" << std::uppercase << std::setw(4)
//           << std::setfill('0') << std::hex << i + 1 << "\t ";
//    } else {
//      cout << ", ";
//    }
//  }
//  cout << endl;
//}
