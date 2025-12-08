'''
Docstring for 2025.src.06
'''

import re
import math
from argparse import ArgumentParser


def part_one(vals):
    
    pattern = "[\d|\+|\*]+"
    for i, ln in enumerate(vals):
        vals[i] = re.findall(pattern, ln)

    grand_total = 0
    for c in range(len(vals[0])):
        intermediate = int(vals[0][c])
        mul = vals[-1][c] == '*'
        for r in range(1, len(vals)-1):
            if mul: intermediate *= int(vals[r][c])
            else:   intermediate += int(vals[r][c])
        grand_total += intermediate

    return grand_total


def part_two(vals):
    
    starts = [i for i, ch in enumerate(vals[-1]) if ch in '+*']
    if not starts:
        raise ValueError("Final row contains no '+' or '*' characters to determine columns.")

    # determine the longest line length so we can pad shorter lines
    max_len = max(len(ln) for ln in vals)

    # compute column widths:
    # for column i (not last): width = next_start - start - 1  (the -1 is the single separator)
    # for last column: width = max_len - start
    widths = []
    for idx, s in enumerate(starts):
        if idx < len(starts) - 1:
            w = starts[idx + 1] - s - 1
        else:
            w = max_len - s
        if w <= 0:
            raise ValueError(f"Computed non-positive width for column {idx} (start={s}, width={w}).")
        widths.append(w)

    # extract columns by slicing each line at start..start+width (pad with spaces if necessary)
    result = []
    for ln in vals:
        padded = ln.ljust(max_len)  # pad right with spaces so slices are safe
        row = [padded[s:s + w] for s, w in zip(starts, widths)]
        result.append(row)

    grand_total = 0
    n_rows = len(result) - 1
    for idx in range(len(widths)):
        nums = []
        for i in range(widths[idx]):
            n = ''
            for j in range(n_rows):
                if result[j][idx][i] == ' ': continue
                n += result[j][idx][i]
            nums.append(int(n))
        mul = '*' in result[-1][idx]
        if mul: grand_total += math.prod(nums)
        else: grand_total += sum(nums)

    return grand_total


def main():

    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)
    args = parser.parse_args()

    try:
        f = open(args.puzzle_path, 'r')
    except:
        print(f"Error opening file: {args.puzzle_path}")
        exit(1)

    vals = f.readlines()
    f.close()

    for i in range(len(vals)):
        vals[i] = vals[i].rstrip('\n')

    if args.part == 1:
        print(f"The grand total is {part_one(vals)}")
    elif args.part == 2:
        print(f"The grand total is {part_two(vals)}")
    else:
        print(f"Invalid part number: {args.part}")
        exit(1)


if __name__ == '__main__':
    main()