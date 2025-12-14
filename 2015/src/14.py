'''
Docstring for 2015.src.14
'''

from argparse import ArgumentParser


class Reindeer():
    def __init__(self, n, s, d, r):
        self.name = n
        self.speed = s
        self.duration = d
        self.rest_time = r

        self.time = 0
        self.distance = 0
        self.moving = True

    def dist(self):
        return self.distance
    
    def go(self, time):
        for i in range(time):
            if self.moving:
                if self.time == self.duration:
                    self.moving = False
                    self.time = 1
                else:
                    self.distance += self.speed
                    self.time += 1
            else:
                if self.time == self.rest_time:
                    self.moving = True
                    self.distance += self.speed
                    self.time = 1
                else:
                    self.time += 1


def parse(ln):
    l = ln.split(' ')
    n = l[0]
    s = int(l[3])
    d = int(l[6])
    r = int(l[13])
    return Reindeer(n, s, d, r)


def main(puzzle, part_two=False):

    reindeers = []
    with open(puzzle, 'r') as f:
        reindeers = [parse(l) for l in f]

    
    if not part_two:
        for r in reindeers: r.go(2503)
        print(max(r.dist() for r in reindeers))
    else:
        points = [0] * len(reindeers)
        for i in range(2503):
            for r in reindeers: r.go(1)
            m = max(r.dist() for r in reindeers)
            for i, r in enumerate(reindeers):
                if r.dist() == m: points[i] += 1

        print(max(points))


    return


if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)

    args = parser.parse_args()

    main(args.puzzle_path, part_two=args.part==2)