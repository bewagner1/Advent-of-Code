import sys
sys.path.append("../puzzles")


def inc_or_dec(levels, two=False):

    inc = (levels[1] - levels[0]) > 0
    
    for i in range(2, len(levels)):

        diff = levels[i] - levels[i-1]

        if (inc and diff < 0) or (not inc and diff > 0):
            return i*10 if two else False

    return True


def step_size(levels, two=False):
    
    for i in range(1, len(levels)):

        diff = abs(levels[i] - levels[i-1])

        if diff > 3 or diff < 1:
            return i*10 if two else False
        
    return True


def get_permutations(levels):
    perms = [levels[1:]]
    for i in range(1, len(levels)):
        perms.append(levels[:i] if i+1 == len(levels) else levels[:i]+levels[i+1:])
    return perms


def test_permutations(perms):

    for p in perms:
        if inc_or_dec(p) and step_size(p):
            return True

    return False


def determine_safety(report, two=False):

    levels = report.split(' ')
    if '\n' in levels[-1]:
        levels[-1] = levels[-1][:-1]

    for i in range(len(levels)):
        levels[i] = int(levels[i])

    safe = inc_or_dec(levels) and step_size(levels)

    if not two or safe:
        return safe

    return test_permutations(get_permutations(levels))


if __name__ == '__main__':

    FILE_PATH = "./puzzles/02.txt"
    with open(FILE_PATH, 'r') as f:
        text = f.readlines()

    part_one = 0
    part_two = 0
    for report in text:
        part_one += 1 if determine_safety(report) else 0
        part_two += 1 if determine_safety(report, two=True) else 0

    print(part_one)
    print(part_two)