import sys
sys.path.append("../puzzles")


def process(text):
    for i, l in enumerate(text):
        if '\n' in l:
            text[i] = l[:-1]
    return text


def bounds_check(r, c, w, h):
    if r < 0 or c < 0:
        return False
    elif r > h or c > w:
        return False
    return True


def is_node(r, c, map):
    return

def part_one(input):

    height = len(input)
    width = len(input[0])

    n_nodes = 0
    for i in range(height):
        for j in range(width):
            if is_node(i, j, input):
                n_nodes += 1

    print(n_nodes)

    

if __name__ == '__main__':
    
    FILE_PATH = "./puzzles/08_ex.txt"
    with open(FILE_PATH, 'r') as f:
        text = f.readlines()

    text = process(text)
    part_one(text)