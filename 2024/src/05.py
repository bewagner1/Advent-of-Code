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

    pages = update.split(',')
    for i, p in enumerate(pages[1:]):
        if p not in hsh.keys():
            continue
        for b in hsh[p]:
            if b in pages[:i+1]:
                return False
            
    return True


def get_middle(update):
    pages = update.split(',')
    mid = len(pages) // 2
    return int(pages[mid])


def part_one(rules, updates):

    sm = 0
    hsh = build_hash(rules)

    for update in updates:
        if validate(hsh, update):
            sm += get_middle(update)

    print(sm)


def fix(hsh, update):

    pages = update.split(',')
    for i in range(1, len(pages)):
        if pages[i] not in hsh.keys():
            continue
        for j in range(i):
            if pages[j] in hsh[pages[i]]:
                temp = pages[i]
                pages[i] = pages[j]
                pages[j] = temp

    return ','.join(pages)


def part_two(rules, updates):

    sm = 0
    hsh = build_hash(rules)

    for update in updates:
        if not validate(hsh, update):
            sm += get_middle(fix(hsh, update))

    print(sm)



if __name__ == '__main__':

    FILE_PATH = "./puzzles/05.txt"

    with open(FILE_PATH, 'r') as f:
        text = f.readlines()

    i = 0
    while text[i] != '\n':
        i += 1
    rules = strip_newln(text[:i])
    updates = strip_newln(text[i+1:])

    part_one(rules, updates)
    part_two(rules, updates)