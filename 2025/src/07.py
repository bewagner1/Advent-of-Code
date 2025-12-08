from pprint import pprint
from argparse import ArgumentParser


def bounds_check(r, c, nr, nc):
    if r < 0 or r >= nr: return False
    if c < 0 or c >= nc: return False
    return True


def split(grid):

    nr = len(grid)
    for i in range(1, len(grid)):
        nc = len(grid[i])
        for j in range(len(grid[i])):

            if grid[i][j] == '^': continue

            up_left = bounds_check(i-1, j-1, nr, nc) and bounds_check(i-2, j-1, nr, nc)
            up_right = bounds_check(i-1, j+1, nr, nc) and bounds_check(i-2, j+1, nr, nc)

            if grid[i-1][j] == '|' or grid[i-1][j] == 'S':
                grid[i] = grid[i][:j] + '|' + grid[i][j+1:]
            elif up_left and grid[i-1][j-1] == '^' and grid[i-2][j-1] == '|':
                grid[i] = grid[i][:j] + '|' + grid[i][j+1:]
            elif up_right and grid[i-1][j+1] == '^' and grid[i-2][j+1] == '|':
                grid[i] = grid[i][:j] + '|' + grid[i][j+1:]

    return grid


def main(grid, part_two=False):

    grid = split(grid)
    count = 0
    for i in range(len(grid)):
        for j in range(len(grid[i])):
            if grid[i][j] == '^' and grid[i-1][j] == '|': count += 1

    if part_two: print(f"There are {2 * count - 1} possible paths")
    else: print(f"There are {count} splits")



if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)
    args = parser.parse_args()
    if args.part != 1 and args.part != 2:
        print(f"Invalid part: {args.parg}")
        exit(1)

    grid = []
    try:
        with open(args.puzzle_path, 'r') as f:
            grid = [l.rstrip('\n') for l in f]
    except:
        print(f"Unable to open file: {args.puzzle_path}")
        exit(1)
    if len(grid) == 0:
        print(f"Error opening file: {args.puzzle_path}")
        exit(1)

    main(grid, part_two=args.part==2)