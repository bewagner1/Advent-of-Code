'''
Docstring for 2015.src.07
'''

from argparse import ArgumentParser
from pprint import pprint


def find_value(circuits, wire, cache=None):
    if cache is None:
        cache = {}
    
    if wire in cache:
        return cache[wire]
    elif wire.isdigit():
        return int(wire)
    
    expr = circuits[wire]
    if 'AND' in expr:
        l, r = expr.split(' AND ')
        result = find_value(circuits, l, cache) & find_value(circuits, r, cache)
    elif 'OR' in expr:
        l, r = expr.split(' OR ')
        result = find_value(circuits, l, cache) | find_value(circuits, r, cache)
    elif 'RSHIFT' in expr:
        l, r = expr.split(' RSHIFT ')
        result = find_value(circuits, l, cache) >> find_value(circuits, r, cache)
    elif 'LSHIFT' in expr:
        l, r = expr.split(' LSHIFT ')
        result = find_value(circuits, l, cache) << find_value(circuits, r, cache)
    elif 'NOT' in expr:
        l = expr.split('NOT ')[-1]
        result = ~find_value(circuits, l, cache) & 0xFFFF  # Mask to 16 bits
    else:
        result = find_value(circuits, expr, cache)
    
    cache[wire] = result
    return result


def main(puzzle):

    circuits = {}
    with open(puzzle, 'r') as f:
        for ln in f:
            x = ln.rstrip('\n').split(' -> ')
            circuits[x[-1]] = x[0]

    a = find_value(circuits, 'a')

    print(f"The value in wire a is {a}")
    circuits['b'] = str(a)
    print(f"The value in wire a is {find_value(circuits, 'a')}")

    return


if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument("puzzle", type=str, help="Path to puzzle")
    args = parser.parse_args()

    main(args.puzzle)
