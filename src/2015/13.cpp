/**
 * Solution to the 2015/12/13 Advent of Code puzzle
 */

#include <exception>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cerr << "Usage: ./13 <path/to/puzzle>" << std::endl;
    return 1;
  }

  std::ifstream puzzle;
  try {
    puzzle.open(argv[1]);
  } catch (const std::exception &e) {
    std::cerr << "ERROR: Could not open puzzle " << argv[1] << '\n'
              << e.what() << std::endl;
    return 1;
  }

  return 0;
}
