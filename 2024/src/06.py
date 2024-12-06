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


def go_up():
    return


def go_down():
    return


def go_left():
    return


def go_right():
    return


def part_one(map):

    h = len(map)
    w = len(map[0])

    x, y, dir = find_agent(map)

    while bounds_check(x, y, w, h):
        if dir == "up":
            x, y = go_up()
            dir = "right"
        elif dir == "right":
            x, y, = go_right()
            dir = "down"
        elif dir == "down":
            x, y, = go_down()
            dir = "left"
        elif dir == "left":
            x, y, = go_left()
            dir = "up"

    print(count(map))



if __name__ == '__main__':

    FILE_PATH = "./puzzles/06_ex.txt"
    with open(FILE_PATH, 'r') as f:
        text = f.readlines()
    
    map = text_to_map(text)

    part_one(map)