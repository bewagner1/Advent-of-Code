"""
Solution to the 2015/12/05 Advent of Code puzzle
"""

from argparse import ArgumentParser
from collections import Counter

def part_one(puzzle):
    with open(puzzle, "r") as f:
        vowels = set(["a", "e", "i", "o", "u"])
        naughty = set(["ab", "cd", "pq","xy"])
        nice = 0
        for ln in f:
            line = ln.rstrip('\n')
            count = Counter(line)
            if sum(count[v] for v in vowels) < 3: continue
            if sum(n in line for n in naughty): continue
            for i in range(len(line) - 1):
                if line[i] == line[i + 1]:
                    nice += 1
                    break
        print(f"There are {nice} nice strings")

def part_two(puzzle):
    with open(puzzle, "r") as f:
        nice = 0
        for ln in f:
            line = ln.rstrip('\n')
            double = False
            space = False

            for i in range(len(line) - 2):
                if not space and line[i] == line[i+2]: space = True
                if not double and i < len(line) - 3:
                    for j in range(i+2, len(line) - 1):
                        if line[i:i+2] == line[j:j+2]:
                            double = True
                            break

            if space and double:
                nice += 1
        print(f"There are {nice} nice strings")

def main():
    parser = ArgumentParser()
    parser.add_argument("puzzle", type=str, help="Path to puzzle")
    args = parser.parse_args()

    part_one(args.puzzle)
    part_two(args.puzzle)

    return

if __name__ == "__main__":
    main()
