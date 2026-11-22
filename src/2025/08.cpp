/**
 * Solution to the 2025/12/08 Advent of Code puzzle
 */

#include <cstddef>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./08 <path/to/puzzle>" << std::endl;
    return 1;
  }

  std::ifstream puzzle(argv[1]);
  if (!puzzle.is_open()) {
    std::cerr << "ERROR: Unable to open puzzle \"" << argv[1] << '\"'
              << std::endl;
    return 1;
  }

  std::vector<std::vector<long>> points;
  long x, y, z;
  char comma;
  while (puzzle >> x >> comma >> y >> comma >> z) {
    points.push_back({x, y, z});
  }
  puzzle.close();

  std::vector<std::vector<double>> dists;
  for (int i = 0; i < points.size() - 1; ++i) {
    std::vector<double> v;
    for (int j = i + 1; j < points.size(); ++j) {
      double xsq = points[i][0] - points[j][0];
      double ysq = points[i][1] - points[j][1];
      double zsq = points[i][2] - points[j][2];

      xsq = xsq * xsq;
      ysq = ysq * ysq;
      zsq = zsq * zsq;

      v.push_back(std::sqrt(xsq + ysq + zsq));
    }
    dists.push_back(v);
  }

  std::priority_queue<double, std::vector<double>, std::greater<double>> heap;
  for (size_t i = 0; i < points.size() - 1; ++i) {
    for (size_t j = i + 1; j < points.size(); ++j) {
      heap.push(dists[i][j - i - 1]);
    }
  }

  std::vector<std::set<size_t>> circuits;
  auto intersects = [](const std::set<size_t> &a,
                       const std::set<size_t> &b) -> bool {
    if (a.empty() || b.empty()) return false;
    for (size_t x : a) {
      if (b.count(x)) return true;
    }
    return false;
  };
  auto consolidate = [&]() -> void {
    bool changed = true;
    while (changed) {
      changed = false;
      for (size_t i = 0; i < circuits.size() && !changed; ++i) {
        for (size_t j = i + 1; j < circuits.size() && !changed; ++j) {
          if (intersects(circuits[i], circuits[j])) {
            circuits[i].insert(circuits[j].begin(), circuits[j].end());
            circuits.erase(circuits.begin() + j);
            changed = true;
          }
        }
      }
    }
  };

  constexpr int MAX_CONNECTIONS = 1000;
  int n = 0;
  size_t r, c;
  while (n < MAX_CONNECTIONS) {
    bool flag = false;
    for (size_t i = 0; i < dists.size(); ++i) {
      for (size_t j = 0; j < dists[i].size(); ++j) {
        if (dists[i][j] == heap.top()) {
          r = i;
          c = j + i + 1;
          flag = true;
          break;
        }
      }
      if (flag) break;
    }

    for (int i = 0; i < circuits.size(); ++i) {
      if (circuits[i].count(r) || circuits[i].count(c)) {
        circuits[i].emplace(r);
        circuits[i].emplace(c);
        n++;
        flag = false;
        break;
      }
    }
    if (flag) {
      std::set<size_t> s = {r, c};
      circuits.emplace_back(s);
      n++;
    }

    consolidate();
    heap.pop();
  }

  std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t>> sizes;
  for (const std::set<size_t> &s : circuits) {
    if (sizes.size() < 3) {
      sizes.push(s.size());
    } else if (s.size() > sizes.top()) {
      sizes.pop();
      sizes.push(s.size());
    }
  }

  unsigned long part_one = 1;
  while (!sizes.empty()) {
    part_one *= sizes.top();
    sizes.pop();
  }
  std::cout << "The product of the sizes of the largest 3 circuits is "
            << part_one << std::endl;

  while (circuits[0].size() < points.size()) {
    bool flag = false;
    for (int i = 0; i < dists.size() - 1; ++i) {
      for (int j = 0; j < dists[i].size(); ++j) {
        if (dists[i][j] == heap.top()) {
          r = i;
          c = j + i + 1;
          flag = true;
          break;
        }
      }
      if (flag) break;
    }

    for (int i = 0; i < circuits.size(); ++i) {
      if (circuits[i].count(r) || circuits[i].count(c)) {
        circuits[i].emplace(r);
        circuits[i].emplace(c);
        n++;
        flag = false;
        break;
      }
    }
    if (flag) {
      std::set<size_t> s = {r, c};
      circuits.emplace_back(s);
      n++;
    }

    consolidate();
    heap.pop();
  }

  std::cout
      << "The prodcut of the x-coordinates of the last two joined boxes is "
      << points[r][0] * points[c][0] << std::endl;

  return 0;
}
