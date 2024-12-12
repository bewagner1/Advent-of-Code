import sys
sys.path.append("../puzzles")



def convert_to_disk(input):
    disk = ""
    i = 0
    for idx, ch in enumerate(input):
        if idx % 2 == 0:
            disk += str(i) * int(ch)
            i += 1
        else:
            disk += '.' * int(ch)

    return disk


def sort_disk(disk):

    l = 0
    r = len(disk) - 1
    while l < r:
        if disk[l] == '.' and disk[r] != '.':
            disk = disk[:l] + disk[r] + disk[l+1:]
            disk = disk[:r] + '.' + disk[r+1:]
            l += 1
            r -= 1
        elif disk[l] == '.' and disk[r] == '.':
            r -= 1
        elif disk[l] != '.':
            l += 1

    return disk


def checksum(sorted_disk):
    check = 0
    for i, ch in enumerate(sorted_disk):
        if ch == '.':
            break
        check += i * int(ch)

    return check


def part_one(input):

    disk = convert_to_disk(input)
    print(disk[:150])
    sorted_disk = sort_disk(disk)
    check = checksum(sorted_disk)
    print(check)



if __name__ == '__main__':

    FILE_PATH = "./puzzles/09.txt"
    with open(FILE_PATH, 'r') as f:
        text = f.readline()

    if '\n' in text:
        text = text[:-1]

    part_one(text)

    pass