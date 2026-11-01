/**
 * Solution to the 2015/12/01 Advent of Code puzzle
 */

#include <exception>
#include <fstream>
#include <iostream>

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
  int position = 0;
  bool basement = false;
  while (puzzle >> c) {
    if (c == '(')
      ++floor;
    else if (c == ')')
      --floor;

    ++position;
    if (floor == -1 && !basement) {
      std::cout << "Santa first enters the basement at position " << position
                << std::endl;
      basement = true;
    }
  }

  std::cout << "Santa ends up at floor " << floor << std::endl;
  return 0;
}
