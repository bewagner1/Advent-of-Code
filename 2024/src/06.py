import sys
sys.path.append("../puzzles")


def find_agent(map):
    for i in range(len(map)):
        for j in range(len(map[0])):
            if map[i][j] == '^':
                return i, j, "up"
            elif map[i][j] == 'v':
                return i, j, "up"
            elif map[i][j] == '<':
                return i, j, "left"
            elif map[i][j] == '>':
                return i, j, "right"
            
    raise ValueError("Agent not found")


def count(map):
    ret = 0
    for i in range(len(map)):
        for j in range(len(map[0])):
            if map[i][j] == 'X':
                ret += 1

    return ret


def bounds_check(row, col, width, height):

    if row < 0 or col < 0:
        return False
    if row >= height or col >= width:
        return False
    
    return True


def strip_newln(s):
    if '\n' in s:
        return list(s)[:-1]
    return list(s)


def text_to_map(input):
    mp = []
    for l in input:
        mp.append(strip_newln(l))
    return mp


def go_up(row, col, map):

    r = row

    while bounds_check(r-1, col, len(map[0]), len(map)):
        map[r][col] = 'X'
        if map[r-1][col] == '#':
            return r
        r -= 1

    map[r][col] = 'X'
    return -1


def go_down(row, col, map):

    r = row

    while bounds_check(r+1, col, len(map[0]), len(map)):
        map[r][col] = 'X'
        if map[r+1][col] == '#':
            return r
        r += 1

    map[r][col] = 'X'
    return -1


def go_left(row, col, map):

    c = col

    while bounds_check(row, c-1, len(map[0]), len(map)):
        map[row][c] = 'X'
        if map[row][c-1] == '#':
            return c
        c -= 1

    map[row][c] = 'X'
    return c


def go_right(row, col, map):

    c = col

    while bounds_check(row, c+1, len(map[0]), len(map)):
        map[row][c] = 'X'
        if map[row][c+1] == '#':
            return c
        c += 1

    map[row][c] = 'X'
    return -1


def part_one(map):

    h = len(map)
    w = len(map[0])

    r, c, dir = find_agent(map)

    while bounds_check(r, c, w, h):
        if dir == "up":
            r = go_up(r, c, map)
            dir = "right"
        elif dir == "right":
            c = go_right(r, c, map)
            dir = "down"
        elif dir == "down":
            r = go_down(r, c, map)
            dir = "left"
        elif dir == "left":
            c = go_left(r, c, map)
            dir = "up"

    print(count(map))



if __name__ == '__main__':

    FILE_PATH = "./puzzles/06.txt"
    with open(FILE_PATH, 'r') as f:
        text = f.readlines()
    
    map = text_to_map(text)

    part_one(map)