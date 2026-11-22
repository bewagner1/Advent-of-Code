/**
 * Solution to the 2025/12/09 Advent of Code puzzle
 */

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./09 <path/to/puzzle>" << std::endl;
    return 1;
  }

  std::ifstream puzzle(argv[1]);
  if (!puzzle.is_open()) {
    std::cerr << "ERROR: Unable to open puzzle \"" << argv[1] << '\"'
              << std::endl;
    return 1;
  }

  std::vector<std::pair<long, long>> points;
  long x, y;
  char comma;
  while (puzzle >> x >> comma >> y) {
    points.push_back({x, y});
  }
  puzzle.close();

  unsigned long part_one = 0;
  for (size_t i = 0; i < points.size() - 1; ++i) {
    for (size_t j = i + 1; j < points.size(); ++j) {
      unsigned long w = std::abs(points[i].first - points[j].first) + 1;
      unsigned long h = std::abs(points[i].second - points[j].second) + 1;
      unsigned long a = w * h;
      if (a > part_one) part_one = a;
    }
  }

  std::cout << "The largest area is " << part_one << std::endl;

  return 0;
}
