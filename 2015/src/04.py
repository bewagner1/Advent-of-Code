'''
Docstring for 2015.src.04
'''

from argparse import ArgumentParser
from hashlib import md5


def main(puzzle, part_two=False):
    
    f = open(puzzle, 'r')
    key = f.read().rstrip('\n')
    f.close()

    i = 0
    while True:

        candidate = key + str(i)
        candidate = candidate.encode()

        hash = md5(candidate).hexdigest()

        if part_two and hash[:6] == '000000':
            print(f"The answer is {i}")
            break
        elif not part_two and hash[:5] == '00000':
            print(f"The answer is {i}")
            break

        i += 1

    return


if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)

    args = parser.parse_args()

    main(args.puzzle_path, part_two=args.part==2)