"""
Solution to the 2025/12/10 Advent of Code puzzle
"""

from argparse import ArgumentParser
import numpy as np
from scipy.optimize import milp, Bounds, LinearConstraint

def main():
    parser = ArgumentParser()
    parser.add_argument("puzzle", type=str, help="Path to puzzle")
    args = parser.parse_args()

    with open(args.puzzle, "r") as f:
        for ln in f:
            parts = ln.rstrip('\n').split(' ')
            lights = [-1 if p == '.' else 1 for p in parts[0][1:-1]]
            buttons = [[int(p) for p in pa[1:-1].split(',')] for pa in parts[1:-1]]
            joltages = [int(p) for p in parts[-1][1:-1].split(',')]

		# Minimize button presses
            
    return

if __name__ == "__main__":
    main()
