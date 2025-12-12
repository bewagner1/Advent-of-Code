'''
Docstring for 2025.src.12
'''


from argparse import ArgumentParser
import re


def parse_puzzle(path):

    presents = []
    regions = []
    pattern = r'[\d]+'

    with open(path, 'r') as f:

        ln = f.readline()
        while ln:
            
            if ':' in ln and 'x' in ln:
                
                r = ln.split(':')
                r[-1] = [int(x) for x in re.findall(pattern, r[-1])]
                regions.append(r)

            elif ':' in ln:

                ln = f.readline()
                p = []
                while ln != '\n':
                    p.append(ln.rstrip())
                    ln = f.readline()
                presents.append(p)
            
            ln = f.readline()

    return presents, regions


def present_area(present):
    count = 0
    for r in range(len(present)):
        for c in range(len(present[r])):
            if present[r][c] == '#': count += 1

    return count


def fit(present, region):
    return region


def valid_region(dims, p_count, presents):

    r = []
    for i in range(dims[0]):
        r.append('.' * dims[1])

    for i, p in enumerate(presents):
        for i in range(p_count[i]):
            r = fit(p, r)

    return present_area(r) == sum(present_area(p) * p_count[i] for i,p in enumerate(presents))


def main(puzzle, part_two=False):

    presents, regions = parse_puzzle(puzzle)

    n_valid = 0
    for r in regions:

        dims = [int(x) for x in r[0].split('x')]

        if dims[0] * dims[1] < sum(present_area(p) * r[1][i] for i,p in enumerate(presents)): continue
        # if valid_region(dims, r[-1], presents): n_valid += 1
        else: n_valid += 1


    print(f"There are {n_valid} regions that fit all the presents litsed")
    return


if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)

    args = parser.parse_args()

    main(args.puzzle_path, part_two=args.part==2)