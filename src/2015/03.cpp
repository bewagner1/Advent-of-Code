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
  puzzle.close();

  // Part 2
  try {
    puzzle.open(argv[1]);
  } catch (const std::exception &e) {
    std::cerr << "ERROR: Unable to open puzzzle - " << e.what() << std::endl;
    return 1;
  }

  int sx = 0, sy = 0, rx = 0, ry = 0;
  char r;
  seen.clear();
  seen.insert({0, 0});
  while (puzzle >> c >> r) {
    if (c == '^') {
      ++sy;
    } else if (c == 'v') {
      --sy;
    } else if (c == '>') {
      ++sx;
    } else if (c == '<') {
      --sx;
    }
    seen.insert({sx, sy});

    if (r == '^') {
      ++ry;
    } else if (r == 'v') {
      --ry;
    } else if (r == '>') {
      ++rx;
    } else if (r == '<') {
      --rx;
    }
    seen.insert({rx, ry});
  }

  std::cout << "Santa and Robo-Santa visit " << seen.size() << " unique houses"
            << std::endl;
  puzzle.close();

  return 0;
}
