
from collections import Counter
import numpy as np

def part_one(infile):

    arr = np.ndarray(5, dtype=[('letter', int), ('frequency', int)])

    total = 0
    with open(infile, 'r') as f:
        for room in f:
            names = ''.join(room.split('-')[:-1])
            c = Counter(names)
            checksum_secid = room.split('[')
            checksum = checksum_secid[-1].rstrip('\n')[:-1]
            secid = int(checksum_secid[0].split('-')[-1])
            for i, kv in enumerate(c.most_common(5)):
                l, f = kv
                arr[i]['letter'] = ord(l)
                arr[i]['frequency'] = -f

            arr.sort(order=['frequency', 'letter'])
            print(arr)
            s = ''
            for i in range(5):
                s += chr(arr[i]['letter'])
            print(s)
            if s == checksum: total += secid
            

    print(total)


def part_two(infile):
    return


def main():
    part_one("test.txt")
    return


if __name__ == '__main__':
    main()