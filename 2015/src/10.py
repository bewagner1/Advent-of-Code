'''
Docstring for 2015.src.10
'''

from argparse import ArgumentParser


def look_and_say(s):

    next_s = ''
    i = 0
    count = 1
    while i < len(s):
        curr = s[i]
        if i+1<len(s) and curr == s[i+1]:
            i += 1
            count += 1
            continue
        next_s += str(count) + curr
        count = 1
        i += 1

    return next_s


def main(puzzle, part_two=False):

    f = open(puzzle, 'r')
    sequence = f.readline().rstrip('\n')
    f.close()

    for i in range(50 if part_two else 40):
        sequence = look_and_say(sequence)

    print(f"The length of the results is {len(sequence)}")

    return


if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)

    args = parser.parse_args()

    main(args.puzzle_path, part_two=args.part==2)