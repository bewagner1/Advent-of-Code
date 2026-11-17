/**
 * Utility functions for Advent of Code puzzles
 */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstddef>
#include <set>
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

static const std::set<char> decs({'0', '1', '2', '3', '4', '5', '6', '7', '8',
                                  '9'});
/**
 * Checks if a string is a decimal
 */
inline bool is_decimal(const std::string &s) {
  for (size_t i = 0; i < s.size(); ++i) {
    if (decs.find(s[i]) == decs.end()) return false;
  }
  return true;
}

/**
 * Checks for valid bounds of a two dimensional array
 */
template <typename T> inline bool bounds_check(T i, T j, T ni, T nj) {
  if (i < 0 || i >= ni) return false;
  if (j < 0 || j >= nj) return false;
  return true;
}

#endif // UTILS_HPP
