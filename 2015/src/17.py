'''
Docstring for 2015.src.17
'''

from argparse import ArgumentParser
from itertools import combinations


def main(puzzle, part_two=False):

    containers = []
    with open(puzzle, 'r') as f: 
        containers = [int(ln.rstrip('\n')) for ln in f]

    total = 0
    min_n_containers = float('inf')
    for i in range(1, len(containers)+1):
        for c in combinations(containers, i):
            if sum(c) != 150 or (part_two and len(c) > min_n_containers): continue
            if part_two:
                if len(c) < min_n_containers:
                    min_n_containers = len(c)
                    total = 1
                elif len(c) == min_n_containers:
                    total += 1
            else:
                total += 1


    print(f"There are {total} combinations")

    return


if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)

    args = parser.parse_args()

    main(args.puzzle_path, part_two=args.part==2)