/**
 * Solution to the 2025/12/04 Advent of Code puzzle
 */

#include "utils.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./04 <path/to/puzzle>" << std::endl;
    return 1;
  }

  std::ifstream puzzle(argv[1]);
  if (!puzzle.is_open()) {
    std::cerr << "ERROR: Could not open puzzle \"" << argv[1] << "\""
              << std::endl;
    return 1;
  }

  std::string ln;
  std::vector<std::string> grid;
  while (std::getline(puzzle, ln)) {
    grid.push_back(ln);
  }
  puzzle.close();

  auto mark = [&]() -> void {
    for (int r = 0; r < grid.size(); ++r) {
      for (int c = 0; c < grid[r].size(); ++c) {
        if (grid[r][c] != '@') continue;
        unsigned short count = 0;
        for (int i = r - 1; i <= r + 1; ++i) {
          for (int j = c - 1; j <= c + 1; ++j) {
            if (!bounds_check(i, j, static_cast<int>(grid.size()),
                              static_cast<int>(grid[r].size())))
              continue;
            if (i == r && j == c) continue;
            if (grid[i][j] == '@' || grid[i][j] == 'x') ++count;
          }
        }
        if (count < 4) grid[r][c] = 'x';
      }
    }
  };

  auto remove = [&]() -> unsigned long {
    unsigned long count = 0;
    for (size_t r = 0; r < grid.size(); ++r) {
      for (size_t c = 0; c < grid[r].size(); ++c) {
        if (grid[r][c] == 'x') {
          ++count;
          grid[r][c] = '.';
        }
      }
    }
    return count;
  };

  unsigned long count = 0;
  mark();
  count += remove();
  std::cout << count << " rolls can be accessed" << std::endl;

  unsigned long x = 1;
  while (x > 0) {
    mark();
    x = remove();
    count += x;
  }
  std::cout << count << " rolls can be accessed" << std::endl;

  return 0;
}
