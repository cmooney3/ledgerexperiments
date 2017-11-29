#include <iostream>
#include <iomanip>
#include "colors.h"
#include "block.h"
#include "genesisBlock.h"

#define BUF_SIZE 1024

using std::cout;
using std::endl;

void PrintBuffer(uint8_t *buf, int64_t len) {
  cout << "buf = \t0x0000\t[";
  for (int i = 0; i < len; i++) {
    cout << std::uppercase << std::setw(2) << std::setfill('0') << std::hex << (int)buf[i];
    if (i == len - 1) {
      cout << "]";
    } else if (i > 0 && i % 8 == 7) {
      cout << endl << "\t0x" << std::uppercase << std::setw(4)
           << std::setfill('0') << std::hex << i + 1 << "\t ";
    } else {
      cout << ", ";
    }
  }
  cout << endl;
}

int main() {
  cout << "Building 'genesis' block...\t";

  GenesisBlock g;
  cout << GREEN << "DONE" << RESET << endl;
  cout << "\tValidate(): ";
  if (g.Validate()) {
    cout << GREEN << "VALID" << RESET << endl;
  }else {
    cout << RED << "INVALID" << RESET << endl;
  }
  cout << "\tSerialize():" << endl;
  uint8_t buf[BUF_SIZE];
  memset(buf, 0, sizeof(buf));
  int64_t len = g.Serialize(buf, BUF_SIZE);
  cout << ((len == 8 * 6) ? GREEN : RED) << "\t\tlen = " << len << RESET << endl;
  PrintBuffer(buf, len);

  return 0;
}
