import sys
sys.path.append("../puzzles")


def bounds_check(row, col, width, height):
    if row < 0 or col < 0:
        return False
    elif row >= height or col >= width:
        return False
    return True


def check_right(puzzle, row, col):
    string = ""
    for i in range(4):
        string += puzzle[row][col+i]
    if string == "XMAS":
        return 1
    return 0


def check_up_right(puzzle, row, col):
    string = ""
    for i in range(4):
        string += puzzle[row-i][col+i]
    if string == "XMAS":
        return 1
    return 0


def check_up(puzzle, row, col):
    string = ""
    for i in range(4):
        string += puzzle[row-i][col]
    if string == "XMAS":
        return 1
    return 0


def check_up_left(puzzle, row, col):
    string = ""
    for i in range(4):
        string += puzzle[row-i][col-i]
    if string == "XMAS":
        return 1
    return 0


def check_left(puzzle, row, col):
    string = ""
    for i in range(4):
        string += puzzle[row][col-i]
    if string == "XMAS":
        return 1
    return 0


def check_down_left(puzzle, row, col):
    string = ""
    for i in range(4):
        string += puzzle[row+i][col-i]
    if string == "XMAS":
        return 1
    return 0


def check_down(puzzle, row, col):
    string = ""
    for i in range(4):
        string += puzzle[row+i][col]
    if string == "XMAS":
        return 1
    return 0


def check_down_right(puzzle, row, col):
    string = ""
    for i in range(4):
        string += puzzle[row+i][col+i]
    if string == "XMAS":
        return 1
    return 0


def part_one(input):
    width = len(input[0])
    height = len(input)
    words_found = 0
    for r in range(height):
        for c in range(width):
            if input[r][c] != "X":
                continue
            # Check Right
            if bounds_check(r, c+3, width, height):
                words_found += check_right(input, r, c)
            # Check Up Right
            if bounds_check(r-3, c+3, width, height):
                words_found += check_up_right(input, r, c)
            # Check Up
            if bounds_check(r-3, c, width, height):
                words_found += check_up(input, r, c)
            # Check Up Left
            if bounds_check(r-3, c-3, width, height):
                words_found += check_up_left(input, r, c)
            # Check Left
            if bounds_check(r, c-3, width, height):
                words_found += check_left(input, r, c)
            # Check Down Left
            if bounds_check(r+3, c-3, width, height):
                words_found += check_down_left(input, r, c)
            # Check Down
            if bounds_check(r+3, c, width, height):
                words_found += check_down(input, r, c)
            # Check Down Right
            if bounds_check(r+3, c+3, width, height):
                words_found += check_down_right(input, r, c)

    print(words_found)


def confirm_xmas(puzzle, r, c):
    string = ""
    for i in range(3):
        string += puzzle[r-i][c+i]
    if string == "MAS":
        return 1
    return 0

def part_two(input):
    width = len(input[0])
    height = len(input)
    xmas_found = 0
    for r in range(height):
        for c in range(width):
            if input[r][c] != "A":
                continue
            if bounds_check(r-1, c-1, width, height) and bounds_check(r+1, c+1, width, height):
                if input[r-1][c-1] == "M" and input[r+1][c+1] == "S":
                    pass
                elif input[r-1][c-1] == "S" and input[r+1][c+1] == "M":
                    pass
                else:
                    continue
            else:
                continue
            if bounds_check(r+1, c-1, width, height) and bounds_check(r-1, c+1, width, height):
                if input[r+1][c-1] == "M" and input[r-1][c+1] == "S":
                    pass
                elif input[r+1][c-1] == "S" and input[r-1][c+1] == "M":
                    pass
                else:
                    continue
            else:
                continue
            xmas_found += 1

    print(xmas_found)

if __name__ == '__main__':
    
    FILE_PATH = "./puzzles/04.txt"
    with open(FILE_PATH, 'r') as f:
        text = f.readlines()

    cleaned = []
    for line in text:
        if '\n' in line:
            cleaned.append(line[:-1])
        else:
            cleaned.append(line)

    part_one(cleaned)
    part_two(cleaned)