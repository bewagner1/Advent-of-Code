'''
Docstring for 2025.src.12
'''


from argparse import ArgumentParser


def parse_puzzle(path):

    presents = []
    regions = []

    with open(path, 'r') as f:
        pass

    return presents, regions


def present_area(present):
    count = 0
    for r in range(len(present)):
        for c in range(len(present[r])):
            if present[r][c] == '#': count += 1

    return count


def valid_region(region, presents):
    return


def main(puzzle, part_two=False):

    # Read in and parse file
    presents, regions = parse_puzzle(puzzle)

    n_valid = 0
    for r in regions:

        dims = r[0].split('x')
        if dims[0] * dims[1] < sum([present_area(p) * r[1][i] for i,p in enumerate(presents)]): continue

        if valid_region(r, presents): n_valid += 1


    print(f"There are {n_valid} regions that fit all the presents litsed")
    return


if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)

    args = parser.parse_args()

    main(args.puzzle_path, part_two=args.part==2)