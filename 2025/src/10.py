'''
Docstring for 2025.src.10
'''

import re
from argparse import ArgumentParser
from itertools import combinations


def read_machine(ln):

    main_pattern = r'\[([.#]+)\]\s+(.*?)\s+\{([\d,]+)\}'
    match = re.match(main_pattern, ln)

    if match:
        pattern = match.group(1)
        coords_section = match.group(2)
        brace_nums = match.group(3)
        
        coord_pattern = r'\((\d+(?:,\d+)*)\)'
        coords = re.findall(coord_pattern, coords_section)
        coords = [''.join([x.strip() for x in m.split(',')]) for m in coords]
        
        # Parse brace numbers as strings
        brace_list = brace_nums.split(',')

    return pattern, coords, brace_list


def press(lights, button):

    for b in button:
        b = int(b)
        if lights[b] == '.': lights = lights[:b] + '#' + lights[b+1:]
        else: lights = lights[:b] + '.' + lights[b+1:]
    return lights


def find_min_presses(machine):

    final_lights, buttons, _ = read_machine(machine)
    lights = '.' * len(final_lights)

    for l in range(1, len(buttons) + 1):
        for c in combinations(buttons, l):
            nl = lights
            for b in c: nl = press(nl, b)
            if nl == final_lights: return l
            

def part2(f):
    from z3 import Solver, Int, Sum, sat

    machines = []
    for parts in [line.strip().split() for line in f]:
        solution = [c == "#" for c in parts[0][1:-1]]
        buttons = [[int(b) for b in button[1:-1].split(",")] for button in parts[1:-1]]
        voltages = [int(v) for v in parts[-1][1:-1].split(",")]
        machines.append([solution, buttons, voltages])

    total = 0
    for _, buttons, voltages in machines:
        solver = Solver()

        bvars = [Int(f"a{n}") for n in range(len(buttons))]
        for b in bvars:
            solver.add(b >= 0)

        for i,v in enumerate(voltages):
            vvars = [bvars[j] for j,button in enumerate(buttons) if i in button]
            solver.add(Sum(vvars) == v)

        while solver.check() == sat:
            model = solver.model()
            n = sum([model[d].as_long() for d in model])
            solver.add(Sum(bvars) < n)

        total += n
    print(f"The minimum number of button presses is {total}")
    
    
def main(machines, part_two=False):

    n_presses = 0
    for l in machines:
        if not part_two: n_presses += find_min_presses(l)

    if not part_two: print(f"The minimum number of button presses is {n_presses}")
    else: part2(machines)

    return


if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)
    args = parser.parse_args()

    try:
        f = open(args.puzzle_path, 'r')
    except:
        print(f"Error opening file: {args.puzzle_path}")
        exit(1)

    vals = f.readlines()
    f.close()

    for i in range(len(vals)):
        vals[i] = vals[i].rstrip('\n')

    main(vals, part_two=args.part==2)