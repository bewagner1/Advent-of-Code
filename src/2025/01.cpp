/**
 * Solution to the 2025/12/01 Advent of Code puzzle
 */

#include <fstream>
#include <iostream>

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
  puzzle.close();

  return 0;
}
