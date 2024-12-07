import sys
sys.path.append("../puzzles")


def get_operator(operator):
    op = operator.split(' ')
    op[0] = op[0][:-1]
    if '\n' in op[-1]:
        op[-1] = op[-1][:-1]
    for i, n in enumerate(op):
        op[i] = int(n)

    return op


def validate(op):

    target = op[0]

    if len(op) == 3:
        if target == op[1]*op[2] or target == op[1]+op[2]:
            return target
        return 0

    total = op[1]

    if target < total + op[2]:
        return 0
    elif target < total * op[2]:
        total += op[2]
        return validate([target, total] + op[3:])
    else:
        if validate([target, total*op[2]] + op[3:]) == target:
            return target
        else:
            return validate([target, total+op[2]] + op[3:])





def part_one(input):

    sum = 0
    for operator in input:
        op = get_operator(operator)
        sum += validate(op)

    print(sum)
    return


if __name__ =='__main__':

    FILE_PATH = "./puzzles/07.txt"
    with open(FILE_PATH, 'r') as f:
        text = f.readlines()

    part_one(text)