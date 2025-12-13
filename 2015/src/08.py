'''
Docstring for 2015.src.08
'''

from argparse import ArgumentParser
from collections import Counter


def parse1(line):

    diff = 2
    seen = set()
    for i, ch in enumerate(line):
        if ch != "\\" or i-1 in seen: continue
        if line[i+1] == 'x': diff += 3
        elif line[i+1] == '\\' or line[i+1] == '\"': diff += 1
        seen.add(i)
    
    return diff


def parse2(line):
    c = Counter(line)
    return sum(c[ch] for ch in ('\"', '\\')) + 2


def main(puzzle, part_two=False):

    total_ch = 0

    with open(puzzle, 'r') as f:
        for ln in f:
            total_ch += parse2(ln.rstrip('\n')) if part_two else parse1(ln.rstrip('\n'))

    print(f"{total_ch}")

    return


if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)

    args = parser.parse_args()

    main(args.puzzle_path, part_two=args.part==2)