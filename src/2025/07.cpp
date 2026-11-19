/**
 * Solution to the 2025/12/07 Advent of Code puzzle
 */

#include "utils.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./07 <path/to/puzzle>" << std::endl;
    return 1;
  }

  std::ifstream puzzle(argv[1]);
  if (!puzzle.is_open()) {
    std::cerr << "ERROR: Unable to open puzzle \"" << argv[1] << "\""
              << std::endl;
    return 1;
  }

  std::string ln;
  std::vector<std::string> path;
  while (std::getline(puzzle, ln)) {
    path.push_back(ln);
  }
  puzzle.close();

  const size_t nr = path.size();
  for (size_t r = 1; r < nr; ++r) {
    const size_t nc = path[r].size();
    for (size_t c = 0; c < nc; ++c) {
      if (path[r][c] == '^') continue;
      if (path[r - 1][c] == '|' || path[r - 1][c] == 'S') {
        path[r][c] = '|';
        continue;
      }
      if (bounds_check(r, c - 1, nr, nc) && path[r][c - 1] == '^') {
        if (bounds_check(r - 1, c - 1, nr, nc) && path[r - 1][c - 1] == '|') {
          path[r][c] = '|';
          continue;
        }
      }
      if (bounds_check(r, c + 1, nr, nc) && path[r][c + 1] == '^') {
        if (bounds_check(r - 1, c + 1, nr, nc) && path[r - 1][c + 1] == '|') {
          path[r][c] = '|';
          continue;
        }
      }
    }
  }

  unsigned long part_one = 0;
  for (size_t r = 1; r < nr; ++r) {
    for (size_t c = 0; c < path[r].size(); ++c) {
      if (path[r][c] == '^' && path[r - 1][c] == '|') ++part_one;
    }
  }

  std::cout << "The beam will be split " << part_one << " times" << std::endl;

  return 0;
}
