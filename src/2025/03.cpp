/**
 * Solution to the 2025/12/03 Advent of Code puzzle
 */

#include <cstddef>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./03 <path/to/puzzle>" << std::endl;
    return 1;
  }

  std::ifstream puzzle(argv[1]);
  if (!puzzle.is_open()) {
    std::cerr << "ERROR: Unable to open puzzle " << argv[1] << std::endl;
    return 1;
  }

  std::string ln;
  unsigned long part_one = 0;
  while (std::getline(puzzle, ln)) {
    int tens = ln[0] - '0', ones = ln[1] - '0';
    for (size_t i = 2; i < ln.size(); ++i) {
      if (ones > tens) {
        tens = ones;
        ones = ln[i] - '0';
        continue;
      }
      if (ln[i] - '0' > ones) ones = ln[i] - '0';
    }
    part_one += 10 * tens + ones;
  }
  puzzle.close();

  std::cout << "The total output joltage is " << part_one << std::endl;

  return 0;
}
