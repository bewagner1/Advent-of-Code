'''
Docstring for 2015.src.07
'''

from argparse import ArgumentParser
from pprint import pprint


def find_value(wire):
    return


def main(puzzle, part_two=False):

    circuits = {}
    with open(puzzle, 'r') as f:
        for ln in f:
            x = ln.rstrip('\n').split(' -> ')
            circuits[x[-1]] = x[0]

    print(f"The value in wire a is {find_value('a')}")

    return


if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)

    args = parser.parse_args()

    main(args.puzzle_path, part_two=args.part==2)