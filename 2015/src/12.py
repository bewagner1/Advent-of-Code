'''
Docstring for 2015.src.12
'''

from argparse import ArgumentParser
from json import load


def sum_json(data, part_two):

    if isinstance(data, list):
        return sum(sum_json(i, part_two) for i in data)
    elif isinstance(data, dict):
        if part_two and "red" in list(data.values()): return 0
        return sum(sum_json(data[i], part_two) for i in data.keys())
    elif isinstance(data, (int, float)):
        return data

    return 0


def main(puzzle, part_two=False):

    with open(puzzle, 'r') as f:
        data = load(f)

    total = sum_json(data, part_two)

    print(f"The sum of all numbers is {total}")
    
    return


if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)

    args = parser.parse_args()

    main(args.puzzle_path, part_two=args.part==2)