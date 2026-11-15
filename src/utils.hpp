/**
 * Utility functions for Advent of Code puzzles
 */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstddef>
#include <string>
#include <vector>

/**
 * Splits a string on a delimiter
 */
inline std::vector<std::string> split(const std::string &s,
                                      const std::string &delim) {

  if (delim == "") return {s};

  std::vector<std::string> v;
  size_t l = 0, r = s.find(delim);
  const size_t sz = delim.size();
  while (r != std::string::npos) {
    v.push_back(s.substr(l, r - l));
    l = r + sz;
    r = s.find(delim, l);
  }
  v.push_back(s.substr(l));
  return v;
}

/**
 * Joins a string on a delimiter
 */
inline std::string join(const std::vector<std::string> &v,
                        const std::string &delim) {
  std::string s = "";
  const size_t sz = v.size();
  if (sz == 0) return s;
  if (sz == 1) return v[0];

  for (size_t i = 0; i < sz - 1; ++i) {
    s += v[i] + delim;
  }
  return s + v.back();
}

#endif // UTILS_HPP
