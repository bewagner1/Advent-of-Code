'''
Docstring for 2015.src.16
'''

from argparse import ArgumentParser


def parse(ln):

    things = {}
    items = ln.split(' ')
    for i in range(2, len(items), 2):
        things[items[i].rstrip(':')] = items[i+1].rstrip(',')

    return things


def main(puzzle, part_two=False):

    aunts = []
    with open(puzzle, 'r') as f:
        aunts = [parse(ln.rstrip('\n')) for ln in f]

    tape = {
        'children': '3',
        'cats': '7',
        'samoyeds': '2',
        'pomeranians': '3',
        'akitas': '0',
        'vizslas': '0',
        'goldfish': '5',
        'trees': '3',
        'cars': '2',
        'perfumes': '1'
        }
    
    gts = ('cats', 'trees')
    lts = ('pomeranians', 'goldfish')

    for i, a in enumerate(aunts):
        flag = True
        for k, v in a.items():
            if part_two:
                if k in gts and tape[k] >= v:
                    flag = False
                    break
                elif k in lts and tape[k] <= v:
                    flag = False
                    break
                elif k not in gts and k not in lts and tape[k] != v:
                    flag = False
                    break
            else:        
                if tape[k] != v:
                    flag = False
                    break
        if flag:
            print(i + 1)
            break


    return


if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)

    args = parser.parse_args()

    main(args.puzzle_path, part_two=args.part==2)