/**
 * Soulution to the 2015/12/06 Advent of Code puzzle
 */

#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./06 <path/to/puzzle>" << std::endl;
    return 1;
  }

  std::ifstream puzzle;
  try {
    puzzle.open(argv[1]);
  } catch (const std::exception &e) {
    std::cerr << "ERROR: Unable to open puzzle - " << e.what() << std::endl;
    return 1;
  }

  constexpr int w = 1000, h = 1000;
  std::vector<size_t> lights(w * h);
  std::string action, status, _through;
  char _comma;
  int bx, by, tx, ty;
  while (puzzle >> action) {
    if (action == "toggle") {
      if (!(puzzle >> bx >> _comma >> by >> _through >> tx >> _comma >> ty)) {
        std::cerr << "ERROR: Unable to read puzzle" << std::endl;
        puzzle.close();
        return 1;
      }
      for (size_t i = bx; i <= tx; ++i) {
        for (size_t j = by; j <= ty; ++j) {
          lights[i * w + j] = !lights[i * w + j];
        }
      }
    } else {
      if (!(puzzle >> status >> bx >> _comma >> by >> _through >> tx >>
            _comma >> ty)) {
        std::cerr << "ERROR: Unable to read puzzle" << std::endl;
        puzzle.close();
        return 1;
      }
      for (size_t i = bx; i <= tx; ++i) {
        for (size_t j = by; j <= ty; ++j) {
          lights[i * w + j] = status == "on" ? 1 : 0;
        }
      }
    }
  }
  puzzle.close();

  size_t count = 0;
  for (size_t i = 0; i < lights.size(); ++i) {
    if (lights[i])
      ++count;
  }

  std::cout << "There are " << count << " lights on" << std::endl;

  return 0;
}
