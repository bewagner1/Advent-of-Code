/**
 * Solution to the 2025/12/02 Advent of Code puzzle
 */

#include "utils.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./02 <path/to/puzzle>" << std::endl;
    return 1;
  }

  std::ifstream puzzle(argv[1]);
  if (!puzzle.is_open()) {
    std::cerr << "ERROR: Unable to open puzzle " << argv[1] << std::endl;
    return 1;
  }

  std::string ln;
  if (!std::getline(puzzle, ln)) {
    std::cerr << "ERROR: Unable to read puzzle" << std::endl;
    return 1;
  }
  puzzle.close();

  unsigned long part_one = 0, part_two = 0;
  std::vector<std::string> ranges = split(ln, ",");
  for (size_t i = 0; i < ranges.size(); ++i) {
    std::vector<std::string> bounds = split(ranges[i], "-");
    long lower = std::stol(bounds[0]), upper = std::stol(bounds[1]);
    for (long v = lower; v <= upper; ++v) {
      std::string vstr = std::to_string(v);
      size_t sz = vstr.size(), mx = std::max(std::sqrt(v), 2.0);

      for (size_t n = 2; n <= mx; ++n) {
        if (sz % n != 0) continue;
        size_t l = sz / n;
        bool invalid = true;
        for (long k = 1; k < n; ++k) {
          if (vstr.substr(0, l) != vstr.substr(k * l, l)) {
            invalid = false;
            break;
          }
        }
        if (invalid) {
          if (n == 2) part_one += v;
          part_two += v;
          break;
        }
      }
    }
  }

  std::cout << "There sum of the invalid IDs is " << part_one << std::endl;
  std::cout << "There sum of the invalid IDs is " << part_two << std::endl;

  return 0;
}
