import sys
sys.path.append("../puzzles")


def strip_newln(input):
    for i, s in enumerate(input):
        if '\n' in s:
            input[i] = s[:-1]
    return input


def build_hash(rules):
    hsh = {}
    for r in rules:
        before, after = r.split('|')
        if before not in hsh.keys():
            hsh[before] = [after]
        elif after in hsh[before]:
            continue
        else:
            hsh[before].append(after)

    return hsh


def validate(hsh, update):
    return


def get_middle(update):
    return



if __name__ == '__main__':

    FILE_PATH = "./puzzles/05_ex.txt"

    with open(FILE_PATH, 'r') as f:
        text = f.readlines()

    i = 0
    while text[i] != '\n':
        i += 1
    rules = strip_newln(text[:i])
    updates = strip_newln(text[i+1:])