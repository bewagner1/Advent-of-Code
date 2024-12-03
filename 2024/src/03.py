import sys
sys.path.append("../puzzles")


def validate(poss):
    '''
    poss must be a 8 or less character string
    '''
    NUMS = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
    if ')' not in poss or ',' not in poss:
        return False

    left = 0
    next_idx = 0
    for i in range(4):
        if poss[i] == ',':
            left = int(poss[:i])
            next_idx = i + 1
            break
        elif poss[i] not in NUMS:
            return False
    
    if poss[next_idx] == ')':
        return False
    
    right = 0
    for i in range(4):
        if poss[next_idx+i] == ')':
            right = int(poss[next_idx:next_idx+i])
            break
        elif poss[next_idx+i] not in NUMS:
            return False
        
    return left * right


def end_validate(poss):

    ln = len(poss)

    NUMS = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
    if ')' not in poss or ',' not in poss:
        return False
    
    left = 0
    next_idx = 0
    for i in range(4):

        if i == ln:
            return False

        if poss[i] == ',':
            left = int(poss[:i])
            next_idx = i + 1
            if next_idx == ln:
                return False
            break
        elif poss[i] not in NUMS:
            return False
        
    if poss[next_idx] not in NUMS:
        return False
    
    right = 0
    for i in range(4):

        if next_idx+i == ln:
            return False
        
        if poss[next_idx+i] == ')':
            right = int(poss[next_idx:next_idx+i])
            break
        elif poss[next_idx+i] not in NUMS:
            return False
        
    return left * right



def main(input, two=False):


    do = "do()"
    dont = "don't()"
    disabled = False
    mul = "mul("

    sum = 0

    for i in range(len(input)-12):

        if two and disabled:
            if input[i:i+4] == do:
                disabled = False

        elif input[i:i+4] == mul:
            val = validate(input[i+4:i+12])
            if val == False:
                continue
            sum += val

        elif two and input[i:i+7] == dont:
            disabled = True

    for i in range(-12, -7):

        if two and disabled:
            if input[i:i+4] == do:
                disabled = False

        elif input[i:i+4] == mul:
            val = end_validate(input[i+4:])
            if val == False:
                continue
            sum += val

        elif two and input[i:i+7] == dont:
            disabled = True

    print(sum)


if __name__ == '__main__':

    FILE_PATH = "./puzzles/03.txt"

    with open(FILE_PATH, 'r') as f:
        text = f.read()

    main(text)
    main(text, two=True)