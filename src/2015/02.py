"""
Solution to the 2015/12/02 Advent of Code puzzle
"""

from argparse import ArgumentParser

def main():
    parser = ArgumentParser()
    parser.add_argument("puzzle", type=str, help="Path to puzzle file")
    args = parser.parse_args()

    with open(args.puzzle) as f:
        wrapping_paper = 0
        for ln in f:
            l, w, h = ln.split("x")
            l, w, h = int(l), int(w), int(h)
            fb, lr, bt = 2 * l * w, 2 * w * h, 2 * l * h
            slack = min(fb, lr, bt) // 2
            wrapping_paper += fb + lr + bt + slack
        print(f"The elves should order {wrapping_paper} square feet of wrapping paper")


    return

if __name__ == "__main__":
    main()
