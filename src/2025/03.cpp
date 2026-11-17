/**
 * Solution to the 2025/12/03 Advent of Code puzzle
 */

#include <cstddef>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./03 <path/to/puzzle>" << std::endl;
    return 1;
  }

  std::ifstream puzzle(argv[1]);
  if (!puzzle.is_open()) {
    std::cerr << "ERROR: Unable to open puzzle " << argv[1] << std::endl;
    return 1;
  }

  std::string ln;
  unsigned long part_one = 0, part_two = 0;
  while (std::getline(puzzle, ln)) {
    int tens = ln[0] - '0', ones = ln[1] - '0';
    int eleven = ln[0] - '0', ten = ln[1] - '0', nine = ln[2] - '0',
        eight = ln[3] - '0', seven = ln[4] - '0', six = ln[5] - '0',
        five = ln[6] - '0', four = ln[7] - '0', three = ln[8] - '0',
        two = ln[9] - '0', one = ln[10] - '0', zero = ln[11] - '0';

    for (size_t i = 2; i < ln.size(); ++i) {
      if (ones > tens) {
        tens = ones;
        ones = ln[i] - '0';
      } else if (ln[i] - '0' > ones) {
        ones = ln[i] - '0';
      }
      if (i < 12) continue;

      if (ten > eleven) {
        eleven = ten;
        ten = nine;
        nine = eight;
        eight = seven;
        seven = six;
        six = five;
        five = four;
        four = three;
        three = two;
        two = one;
        one = zero;
        zero = ln[i] - '0';
      } else if (nine > ten) {
        ten = nine;
        nine = eight;
        eight = seven;
        seven = six;
        six = five;
        five = four;
        four = three;
        three = two;
        two = one;
        one = zero;
        zero = ln[i] - '0';
      } else if (eight > nine) {
        nine = eight;
        eight = seven;
        seven = six;
        six = five;
        five = four;
        four = three;
        three = two;
        two = one;
        one = zero;
        zero = ln[i] - '0';
      } else if (seven > eight) {
        eight = seven;
        seven = six;
        six = five;
        five = four;
        four = three;
        three = two;
        two = one;
        one = zero;
        zero = ln[i] - '0';
      } else if (six > seven) {
        seven = six;
        six = five;
        five = four;
        four = three;
        three = two;
        two = one;
        one = zero;
        zero = ln[i] - '0';
      } else if (five > six) {
        six = five;
        five = four;
        four = three;
        three = two;
        two = one;
        one = zero;
        zero = ln[i] - '0';
      } else if (four > five) {
        five = four;
        four = three;
        three = two;
        two = one;
        one = zero;
        zero = ln[i] - '0';
      } else if (three > four) {
        four = three;
        three = two;
        two = one;
        one = zero;
        zero = ln[i] - '0';
      } else if (two > three) {
        three = two;
        two = one;
        one = zero;
        zero = ln[i] - '0';
      } else if (one > two) {
        two = one;
        one = zero;
        zero = ln[i] - '0';
      } else if (zero > one) {
        one = zero;
        zero = ln[i] - '0';
      } else if (ln[i] - '0' > zero) {
        zero = ln[i] - '0';
      }
    }
    part_one += 10 * tens + ones;
    part_two += 1e11 * eleven + 1e10 * ten + 1e9 * nine + 1e8 * eight +
                1e7 * seven + 1e6 * six + 1e5 * five + 1e4 * four +
                1e3 * three + 100 * two + 10 * one + zero;
  }
  puzzle.close();

  std::cout << "The total output joltage is " << part_one << std::endl;
  std::cout << "The total output joltage is " << part_two << std::endl;

  return 0;
}
