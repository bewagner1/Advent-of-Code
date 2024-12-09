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


def validate(op, two=False):

    target = op[0]

    if len(op) == 3:
        if two:
            if target == op[1]*op[2] or target == op[1]+op[2] or target == int(str(op[1])+str(op[2])):
                return target
        elif target == op[1]*op[2] or target == op[1]+op[2]:
            return target
        return 0

    total = op[1]

    if target < total + op[2]:
        return 0
    elif target < total * op[2]:
        total += op[2]
        return validate([target, total] + op[3:], two=two)
    elif target < int(str(total) + str(op[2])) and two:
        if validate([target, total*op[2]] + op[3:], two=two) == target:
            return target
        else:
            return validate([target, total+op[2]] + op[3:], two=two)
    else:
        if validate([target, int(str(total)+str(op[2]))] + op[3:], two=two) == target and two:
            return target
        elif validate([target, total*op[2]] + op[3:], two=two) == target:
            return target
        else:
            return validate([target, total+op[2]] + op[3:], two=two)

def part_one(input):

    sum = 0
    for operator in input:
        op = get_operator(operator)
        sum += validate(op)

    print(sum)
    return


def part_two(input):

    sum = 0
    for operator in input:
        op = get_operator(operator)
        sum += validate(op, two=True)

    print(sum)
    return


if __name__ =='__main__':

    FILE_PATH = "./puzzles/07.txt"
    with open(FILE_PATH, 'r') as f:
        text = f.readlines()

    part_one(text)
    part_two(text)