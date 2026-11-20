/**
 * Solution to the 2025/12/08 Advent of Code puzzle
 */

#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: ./08 <path/to/puzzle>" << std::endl;
    return 1;
  }

  std::ifstream puzzle(argv[1]);
  if (!puzzle.is_open()) {
    std::cerr << "ERROR: Unable to open puzzle \"" << argv[1] << '\"'
              << std::endl;
    return 1;
  }

  std::vector<std::vector<unsigned long>> pos;
  std::string ln;
  while (std::getline(puzzle, ln)) {
    std::vector<std::string> l = split(ln, ",");
    pos.push_back({std::stoul(l[0]), std::stoul(l[1]), std::stoul(l[2])});
  }
  puzzle.close();

  return 0;
}
