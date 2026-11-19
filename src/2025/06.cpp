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

  const std::vector<std::string> &last = lines.back();
  std::vector<int> widths;
  int count = 1;
  for (size_t i = 1; i < last.size(); ++i) {
    if (last[i] == "*" || last[i] == "+") {
      widths.push_back(count);
      count = 1;
      continue;
    }
    ++count;
  }
  widths.push_back(count);

  std::vector<std::string> joined;
  for (size_t i = 0; i < lines.size(); ++i) {
    joined.push_back(join(lines[i], " "));
  }

  unsigned long part_two = 0;
  size_t idx = 0;
  for (size_t w = 0; w < widths.size(); ++w) {
    const int width = widths[w];
    unsigned long temp;
    switch (joined.back()[idx]) {
    case '*':
      temp = 1;
      for (int i = 0; i < width; ++i) {
        std::string n = "";
        for (size_t r = 0; r < joined.size() - 1; ++r) {
          if (joined[r][idx + i] != ' ') n += joined[r][idx + i];
        }
        temp *= std::stoul(n);
      }
      part_two += temp;
      break;
    case '+':
      temp = 0;
      for (int i = 0; i < width; ++i) {
        std::string n = "";
        for (size_t r = 0; r < joined.size() - 1; ++r) {
          if (joined[r][idx + i] != ' ') n += joined[r][idx + i];
        }
        temp += std::stoul(n);
      }
      part_two += temp;
      break;
    default:
      std::cerr << "ERROR: Invalid operation encountered " << joined.back()[idx]
                << std::endl;
      return 1;
    }
    idx += width + 1;
  }

  std::cout << "The grand total is " << part_two << std::endl;

  return 0;
}
