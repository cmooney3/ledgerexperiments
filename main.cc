#include <iostream>
#include "colors.h"

using std::cout;
using std::endl;

int main() {
  bool success = false;
  cout << YELLOW << "Starting Ledger Test." << RESET << endl;
  cout << YELLOW << "Final Result: " << RESET;
  if (success) {
    cout << GREEN << "PASS" << RESET << endl;
  } else {
    cout << RED << "FAIL" << RESET << endl;
  }

  return 0;
}
