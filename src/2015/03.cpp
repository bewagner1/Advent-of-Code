/**
 * Solution to the 2015/12/03 Advent of Code puzzle
 */

#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <utility>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cerr << "Usage: ./03 <path/to/puzzle>" << std::endl;
    return 1;
  }

  std::set<std::pair<int, int>> seen;
  int x = 0, y = 0;
  seen.insert({x, y});

  // Part 1
  std::ifstream puzzle;
  try {
    puzzle.open(argv[1]);
  } catch (const std::exception &e) {
    std::cerr << "ERROR: Unable to open puzzle - " << e.what() << std::endl;
    return 1;
  }

  char c;
  while (puzzle >> c) {
    if (c == '^') {
      ++y;
    } else if (c == 'v') {
      --y;
    } else if (c == '<') {
      --x;
    } else if (c == '>') {
      ++x;
    }
    seen.insert({x, y});
  }

  std::cout << "Santa visits " << seen.size() << " unique houses" << std::endl;

  return 0;
}
