/**
 * Solution to the 2025/12/09 Advent of Code puzzle
 */

#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <utility>
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

  auto on = [&](const std::pair<long, long> &p) -> bool {
    const size_t n = points.size();
    const long x = p.first, y = p.second;

    size_t crossings = 0;
    for (size_t i = 0; i < n; ++i) {
      const std::pair<long, long> &p1 = points[i];
      const std::pair<long, long> &p2 = points[(i + 1) % n];
      const long x1 = p1.first, x2 = p2.first;
      const long y1 = p1.second, y2 = p2.second;
      const long minX = std::min(x1, x2), maxX = std::max(x1, x2);
      const long minY = std::min(y1, y2), maxY = std::max(y1, y2);

      if (y1 == y2 && y1 == y && x >= minX && x <= maxX) return true;
      if (x1 == x2) {
        if (x == x1 && y >= minY && y < maxY) return true;
        if (x1 > x && y >= minY && y < maxY) ++crossings;
      }
    }

    return crossings % 2 == 1;
  };

  auto fully = [&](size_t i, size_t j) -> bool {
    const long minX = std::min(points[i].first, points[j].first);
    const long maxX = std::max(points[i].first, points[j].first);
    const long minY = std::min(points[i].second, points[j].second);
    const long maxY = std::max(points[i].second, points[j].second);

    if (!on({minX, minY})) return false;
    if (!on({minX, maxY})) return false;
    if (!on({maxX, minY})) return false;
    if (!on({maxX, maxY})) return false;

    for (long x = minX + 1; x < maxX; ++x) {
      if (!on({x, minY})) return false;
      if (!on({x, maxY})) return false;
    }
    for (long y = minY + 1; y < maxY; ++y) {
      if (!on({minX, y})) return false;
      if (!on({maxX, y})) return false;
    }
    return true;
  };

  unsigned long part_one = 0, part_two = 0;
  for (size_t i = 0; i < points.size() - 1; ++i) {
    for (size_t j = i + 1; j < points.size(); ++j) {
      unsigned long w = std::abs(points[i].first - points[j].first) + 1;
      unsigned long h = std::abs(points[i].second - points[j].second) + 1;
      unsigned long a = w * h;

      if (a > part_one) part_one = a;
      if (a <= part_two) continue;
      if (fully(i, j)) part_two = a;
    }
  }

  std::cout << "The largest area is " << part_one << std::endl;
  std::cout << "The largest area is " << part_two << std::endl;

  return 0;
}
