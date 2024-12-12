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


def search(r, c, input):
    width = len(input[0])
    height = len(input)
    count = 0
    for i in range(len(input)):
        for j in range(len(input[0])):
            if r == i and c == j:
                continue
            delta_h = r - i
            delta_w = c - j
            if input[i][j] == input[r][c] and bounds_check(r+2*delta_h, c+2*delta_w, width, height):
                count += 1

    return count

def part_one(input):

    height = len(input)
    width = len(input[0])

    n_nodes = 0
    for i in range(height):
        for j in range(width):
            if input[i][j] != '.' and search(i, j, input):
                n_nodes += 1

    print(n_nodes)

    

if __name__ == '__main__':
    
    FILE_PATH = "./puzzles/08_ex.txt"
    with open(FILE_PATH, 'r') as f:
        text = f.readlines()

    text = process(text)
    part_one(text)