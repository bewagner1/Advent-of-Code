'''
Docstring for 2025.src.04
'''

from argparse import ArgumentParser


def bounds_check(r,c,nr,nc):
    if r < 0 or r >= nr: return False
    if c < 0 or c >= nc: return False
    return True


def count_accessible(grid, part_two=False):

    n_rows = len(grid)
    n_cols = len(grid[0])

    total = 0
    count = 0
    marked = []
    for row in range(n_rows):
        for col in range(n_cols):

            if grid[row][col] != '@': continue

            for r in (row-1, row, row+1):
                for c in (col-1, col, col+1):

                    if r == row and c == col: continue
                    if not bounds_check(r, c, n_rows, n_cols): continue
                    if grid[r][c] == '@': count += 1

            if count < 4: 
                total += 1
                if part_two: marked.append((row,col))
            count = 0
    if part_two:
        for r,c in marked:
            grid[r] = grid[r][:c] + '.' + grid[r][c+1:]
    
    return total


def main(path, part):

    if not (part == 1 or part == 2):
        raise ValueError("Part must be 1 or 2")
    
    f = open(path, 'r')
    grid = f.readlines()
    f.close()

    for i in range(len(grid)):
        grid[i] = grid[i].strip()

    total = 0
    round_total = count_accessible(grid, part_two=part==2)
    while round_total > 0 and part == 2:
        total += round_total
        round_total = count_accessible(grid, part_two=part==2)

    if part == 1: total += round_total
    print(total)


if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)

    args = parser.parse_args()

    main(args.puzzle_path, args.part)