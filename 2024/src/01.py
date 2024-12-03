from typing import Counter
import sys
sys.path.append("../puzzles")

def get_nums(line, valid, last=False):

    left = ""
    i = 0
    while line[i] in valid:
        left += line[i]
        i += 1

    right = ""
    i = -2
    if last:
        i += 1
    while line[i] in valid:
        right = line[i] + right
        i -= 1

    return int(left), int(right)


def get_lists(input, valid):

    left, right = [], []
    for line in input[:-1]:
        l, r = get_nums(line, valid)
        left.append(l)
        right.append(r)
    
    l, r = get_nums(input[-1], valid, last=True)
    left.append(l)
    right.append(r)

    return sorted(left), sorted(right)


def part_one(input, valid):

    left, right = get_lists(input, valid)

    dist = 0
    for i in range(len(left)):
        dist += abs(left[i] - right[i])

    print(dist)


def part_two(input, valid):

    left, right = get_lists(input, valid)

    c = Counter(right)

    sim_score = 0
    for loc in left:
        if loc in c:
            sim_score += loc * c[loc]

    print(sim_score)


if __name__ == '__main__':

    FILE_PATH = "./puzzles/01.txt"
    NUMS = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']

    with open(FILE_PATH, 'r') as f:
        text = f.readlines()

    part_one(text, NUMS)
    part_two(text, NUMS)