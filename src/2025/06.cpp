/**
 * Solution to the 2025/12/06 Advent of Code puzzle
 */

#include "utils.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./06 <path/to/puzzle>" << std::endl;
    return 1;
  }

  std::ifstream puzzle(argv[1]);
  if (!puzzle.is_open()) {
    std::cerr << "ERROR: Unable to open puzzle \"<< argv[1] << \"";
    return 1;
  }

  std::string ln;
  std::vector<std::vector<std::string>> lines;
  while (std::getline(puzzle, ln)) {
    lines.push_back(split(ln, " "));
  }
  puzzle.close();

  std::vector<std::vector<unsigned long>> nums;
  for (size_t i = 0; i < lines.size() - 1; ++i) {
    std::vector<unsigned long> n;
    for (size_t j = 0; j < lines[i].size(); ++j) {
      if (is_decimal(lines[i][j])) n.push_back(std::stoul(lines[i][j]));
    }
    nums.push_back(n);
  }

  unsigned long part_one = 0;
  size_t i = 0, j = 0;
  while (i < lines.back().size()) {
    if (lines.back()[i] == "*") {
      unsigned long temp = 1;
      for (size_t k = 0; k < nums.size(); ++k) {
        temp *= nums[k][j];
      }
      part_one += temp;
      ++j;
    } else if (lines.back()[i] == "+") {
      unsigned long temp = 0;
      for (size_t k = 0; k < nums.size(); ++k) {
        temp += nums[k][j];
      }
      part_one += temp;
      ++j;
    }
    ++i;
  }

  std::cout << "The grand total is " << part_one << std::endl;

  return 0;
}
