"""
Solution to the 2015/12/04 Advent of Code puzzle
"""

from hashlib import md5
from argparse import ArgumentParser

def main():
    parser = ArgumentParser()
    parser.add_argument("puzzle", type=str, help="Path to puzzle")
    args = parser.parse_args()

    key = ""
    with open(args.puzzle, 'r') as f:
        key = f.read().rstrip('\n')

    val = 0
    while True:
        hash = md5((key + str(val)).encode()).hexdigest()
        if (hash[:5] == "00000"):
            print(f"The lowest positive number is {val} for a hash with 5 leading zeros")
            break
        val += 1

    val = 0
    while True:
        hash = md5((key + str(val)).encode()).hexdigest()
        if (hash[:6] == "000000"):
            print(f"The lowest positive number is {val} for a hash with 6 leading zeros")
            break
        val += 1

    return

if __name__ == "__main__":
    main()
