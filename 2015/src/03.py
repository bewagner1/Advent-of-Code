'''
Docstring for 2015.src.03
'''


from argparse import ArgumentParser


def main(puzzle, part_two=False):

    with open(puzzle, 'r') as f:

        seen = set()
        santa_x = 0
        santa_y = 0
        robo_x = 0
        robo_y = 0

        seen.add((0,0))

        i = 0
        while True:
            ch = f.read(1)
            if not ch: break

            if part_two and i % 2:
                if ch == '^': robo_y += 1
                if ch == '>': robo_x += 1
                if ch == 'v': robo_y -= 1
                if ch == '<': robo_x -= 1
                seen.add((robo_x,robo_y))
            else:
                if ch == '^': santa_y += 1
                if ch == '>': santa_x += 1
                if ch == 'v': santa_y -= 1
                if ch == '<': santa_x -= 1
                seen.add((santa_x,santa_y))

            i += 1

    print(f"{len(seen)} houses get at least one present")

    return


if __name__ == '__main__':
    
    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)

    args = parser.parse_args()

    main(args.puzzle_path, part_two=args.part==2)