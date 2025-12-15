'''
Docstring for 2015.src.17
'''

from argparse import ArgumentParser
from itertools import combinations
from math import prod


def main(puzzle, part_two=False):

    packages = []
    with open(puzzle, 'r') as f: 
        packages = [int(ln.rstrip('\n')) for ln in f]

    total = sum(packages)
    n_groups = 4 if part_two else 3
    total_per_group = total // n_groups
    best = packages
    flag = False
    for i in range(1, len(packages)+1):
        for c in combinations(packages, i):
            if len(c) > len(best): 
                flag = True
                break    
            elif sum(c) != total_per_group: continue
            if len(c) < len(best) or prod(c) < prod(best): best = c

        if flag: break


    print(prod(best))

    return


if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)

    args = parser.parse_args()

    main(args.puzzle_path, part_two=args.part==2)