'''
Docstring for 2025.src.11
'''

from argparse import ArgumentParser


def follow_path(device, rack, end, memo=None):
    if memo is None: memo = {}
    
    if device in memo: return memo[device]
    
    if end in rack[device]: result = 1
    else: result = sum(0 if d == 'out' else follow_path(d, rack, end, memo) for d in rack[device])
    
    memo[device] = result
    return result


def main(puzzle, part_two=False):

    file = open(puzzle, 'r')
    f = file.readlines()
    file.close()

    for i, l in enumerate(f):
        device = l.rstrip('\n').split(":")
        f[i] = {device[0] : device[1].split(' ')[1:]}

    joined = {}
    for d in f:
        joined.update(d)

    if not part_two: print(f"There are {follow_path('you', joined, 'out')} possible paths")
    else: 
        fft_out = follow_path('fft', joined, 'out')
        dac_out = follow_path('dac', joined, 'out')
        fft_dac = follow_path('fft', joined, 'dac')
        dac_fft = follow_path('dac', joined, 'fft')
        svr_fft = follow_path('svr', joined, 'fft')
        svr_dac = follow_path('svr', joined, 'dac')

        total = svr_dac * dac_fft * fft_out + svr_fft * fft_dac * dac_out
        print(f"There are {total} possible paths")
    
    return


if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)

    args = parser.parse_args()

    main(args.puzzle_path, part_two=args.part==2)