/**
 * Solution to the 2025/12/05 Advent of Code puzzle
 */

#include "utils.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./05 <path/to/puzzle>" << std::endl;
    return 1;
  }

  std::ifstream puzzle(argv[1]);
  if (!puzzle.is_open()) {
    std::cerr << "ERROR: Unable to open puzzle \"" << argv[1] << "\""
              << std::endl;
    return 1;
  }

  std::vector<std::pair<long, long>> ranges;

  std::string ln;
  while (std::getline(puzzle, ln)) {
    if (ln == "") break;
    std::vector<std::string> range = split(ln, "-");
    ranges.push_back({std::stol(range[0]), std::stol(range[1])});
  }

  std::vector<std::pair<long, long>> merged;
  std::sort(ranges.begin(), ranges.end(),
            [](std::pair<long, long> &a, std::pair<long, long> &b) {
              return a.first < b.first;
            });

  merged.push_back(ranges[0]);
  for (size_t i = 1; i < ranges.size(); ++i) {
    std::pair<long, long> &last = merged.back();
    std::pair<long, long> &curr = ranges[i];
    if (curr.first <= last.second) {
      last.second = std::max(last.second, curr.second);
    } else {
      merged.push_back(curr);
    }
  }

  unsigned long part_one = 0, part_two = 0;
  while (std::getline(puzzle, ln)) {
    long v = std::stol(ln);
    for (size_t i = 0; i < merged.size(); ++i) {
      if (v >= merged[i].first && v <= merged[i].second) {
        ++part_one;
        continue;
      }
    }
  }
  puzzle.close();

  for (size_t i = 0; i < merged.size(); ++i) {
    part_two += merged[i].second - merged[i].first + 1;
  }

  std::cout << part_one << " available IDs are fresh" << std::endl;
  std::cout << part_two << " IDs are considered fresh" << std::endl;

  return 0;
}
