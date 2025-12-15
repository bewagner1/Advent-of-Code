'''
Docstring for 2015.src.23
'''

from argparse import ArgumentParser


def main(puzzle, part_two=False):

    instructions = []
    with open(puzzle, 'r') as f:
        instructions = [ln.rstrip('\n') for ln in f]

    a, b, i = 0, 0, 0
    if part_two: a = 1
    while i < len(instructions):

        curr = instructions[i].split(' ')
        
        if curr[0] == 'hlf':
            if 'a' in curr[1]: a //= 2
            else: b //= 2
            i += 1
        elif curr[0] == 'tpl':
            if 'a' in curr[1]: a *= 3
            else: b *= 3
            i += 1
        elif curr[0] == 'inc':
            if 'a' in curr[1]: a += 1
            else: b += 1
            i += 1
        elif curr[0] == 'jmp':
            i += int(curr[1])
        elif curr[0] == 'jie':
            if 'a' in curr[1] and a % 2 == 0:   i += int(curr[2])
            elif 'b' in curr[1] and b % 2 == 0: i += int(curr[2])
            else: i += 1
        elif curr[0] == 'jio':
            if 'a' in curr[1] and a == 1:   i += int(curr[2])
            elif 'b' in curr[1] and b == 1: i += int(curr[2])
            else: i += 1


    print(b)
    return


if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)

    args = parser.parse_args()

    main(args.puzzle_path, part_two=args.part==2)