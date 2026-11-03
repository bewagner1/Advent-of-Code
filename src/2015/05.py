"""
Solution to the 2015/12/05 Advent of Code puzzle
"""

from argparse import ArgumentParser
from collections import Counter

def main():
    parser = ArgumentParser()
    parser.add_argument("puzzle", type=str, help="Path to puzzle")
    args = parser.parse_args()

    with open(args.puzzle, "r") as f:
        vowels = set(["a", "e", "i", "o", "u"])
        naughty = set(["ab", "cd", "pq","xy"])
        count = 0
        for ln in f:
            line = ln.rstrip('\n')
            char_count = Counter(line)
            if sum(char_count[v] for v in vowels) < 3: continue
            if sum(n in line for n in naughty): continue
            for i in range(len(line) - 1):
                if line[i] == line[i + 1]:
                    count += 1
                    break
        print(f"There are {count} nice strings")

    return

if __name__ == "__main__":
    main()
