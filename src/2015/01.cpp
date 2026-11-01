/**
 * Solution to the 2015/12/01 Advent of Code puzzle
 */

#include <exception>
#include <fstream>
#include <iostream>
#include <stack>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cerr << "Usage: ./01 <path/to/puzzle>" << std::endl;
    return 1;
  }

  std::ifstream puzzle;
  try {
    puzzle.open(argv[1]);
  } catch (const std::exception &e) {
    std::cerr << "Could not open puzzle file: ";
    std::cerr << argv[1];
    std::cerr << "\nERROR: " << e.what() << std::endl;
    if (puzzle.is_open())
      puzzle.close();
    return 1;
  }

  char c;
  int floor = 0;
  while (puzzle >> c) {
    if (c == '(')
      ++floor;
    else if (c == ')')
      --floor;
  }

  std::cout << floor << std::endl;
  return 0;
}
