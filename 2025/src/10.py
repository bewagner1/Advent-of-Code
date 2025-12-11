'''
Docstring for 2025.src.10
'''

import re
from argparse import ArgumentParser


def read_machine(ln):

    main_pattern = r'\[([.#]+)\]\s+(.*?)\s+\{([\d,]+)\}'
    match = re.match(main_pattern, ln)

    if match:
        pattern = match.group(1)
        coords_section = match.group(2)
        brace_nums = match.group(3)
        
        coord_pattern = r'\((\d+)(?:,(\d+))?\)'
        coords = []
        for coord_match in re.finditer(coord_pattern, coords_section):
            if coord_match.group(2):
                coords.append(coord_match.group(1) + coord_match.group(2))
            else:
                coords.append(coord_match.group(1))
        
        # Parse brace numbers as strings
        brace_list = "".join(brace_nums.split(','))

    return pattern, coords, brace_list


def press(lights, button):
    return


def find_min_presses(machine):

    final_lights, buttons, joltage = read_machine(machine)
    lights = '.' * len(final_lights)
    next_lights = lights

    n_presses = []
    for b in buttons:
        next_lights = press(lights, b)
        if next_lights == final_lights: return 1

    return min(n_presses)

        


def main(machines, part_two=False):

    n_presses = 0
    for l in machines:
        if not part_two: n_presses += find_min_presses(l)

    if not part_two: print(f"The minimum number of button presses is {n_presses}")

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