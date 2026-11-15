/**
 * Solution to the 2025/12/01 Advent of Code puzzle
 */

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./01 <path/to/puzzle>" << std::endl;
    return 1;
  }

  std::ifstream puzzle(argv[1]);
  if (!puzzle.is_open()) {
    std::cerr << "ERROR: Unable to open puzzle " << argv[1] << std::endl;
    return 1;
  }

  std::string ln;
  short n;
  short pos = 50;
  unsigned long part_one = 0, part_two = 0;
  while (std::getline(puzzle, ln)) {
    n = std::stoi(ln.substr(1));
    switch (ln.at(0)) {
    case 'L':
      for (short i = 0; i < n; ++i) {
        --pos;
        if (pos == 0) ++part_two;
        if (pos < 0) pos = 99;
      }
      break;
    case 'R':
      for (short i = 0; i < n; ++i) {
        ++pos;
        if (pos > 99) pos = 0;
        if (pos == 0) ++part_two;
      }
      break;
    default:
      std::cerr << "ERROR: Invalid direction encountered \"" << ln[0] << "\""
                << std::endl;
      return 1;
    }
    if (pos == 0) {
      ++part_one;
    }
  }
  puzzle.close();

  std::cout << "The dial points at zero " << part_one << " times" << std::endl;
  std::cout << "The dial points at zero " << part_two << " times" << std::endl;

  return 0;
}
