'''
Docstring for 2015.src.05
'''

from argparse import ArgumentParser
from collections import Counter


def is_nice1(string):

    char_count = Counter(string)
    if sum(char_count[v] for v in 'aeiou') < 3: return False

    naughty_substrs = ('ab', 'cd', 'pq', 'xy')
    double_flag = False
    for i in range(len(string) - 1):
        if string[i] == string[i+1]:
            double_flag = True
        if string[i:i+2] in naughty_substrs: return False
        
    return double_flag


def is_nice2(string):

    double_flag = False
    space_flag = False

    for i in range(len(string) - 2):
        
        if not space_flag and string[i] == string[i+2]: space_flag = True

        if not double_flag and i < len(string) - 3:
            for j in range(i+2, len(string) - 1):
                if string[i:i+2] == string[j:j+2]:
                    double_flag = True
                    break

    return double_flag and space_flag


def main(puzzle, part_two=False):
    
    n_nice = 0
    with open(puzzle, 'r') as f:
        for ln in f.readlines():
            if part_two and is_nice2(ln.rstrip('\n')): n_nice += 1
            elif not part_two and is_nice1(ln.rstrip('\n')): n_nice += 1

    print(f"There are {n_nice} nice strings")
    
    return


if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)

    args = parser.parse_args()

    main(args.puzzle_path, part_two=args.part==2)