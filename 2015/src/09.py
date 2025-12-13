'''
Docstring for 2015.src.09
'''

from argparse import ArgumentParser


def upper_triangular_to_full(upper_tri):
    """
    Convert upper triangular matrix to full symmetric matrix.
    
    Args:
        upper_tri: List of lists representing upper triangular part (no diagonal)
                   e.g., [[10, 15, 20], [35, 25], [30]] for 4 nodes
    
    Returns:
        Full symmetric distance matrix
    """
    n = len(upper_tri) + 1  # Number of nodes
    full_matrix = [[0] * n for _ in range(n)]
    
    # Fill upper triangular part
    for i in range(n - 1):
        for j in range(len(upper_tri[i])):
            full_matrix[i][i + j + 1] = upper_tri[i][j]
            full_matrix[i + j + 1][i] = upper_tri[i][j]  # Symmetric
    
    return full_matrix


def held_karp(dist_matrix, return_to_start=False, start_node=None):
    """
    Solves TSP using Held-Karp dynamic programming algorithm.
    
    Args:
        dist_matrix: Either a full 2D matrix or upper triangular list
                     Upper triangular: [[10, 15, 20], [35, 25], [30]]
                     Full matrix: [[0, 10, 15, 20], [10, 0, 35, 25], ...]
        return_to_start: If True, return to starting node (TSP cycle)
                        If False, just visit all nodes once (Hamiltonian path)
        start_node: Starting node index. If None, tries all nodes and returns best path.
        
    Returns:
        tuple: (min_cost, path) where path is list of node indices
    """
    # Check if input is upper triangular format
    if dist_matrix and isinstance(dist_matrix[0], list):
        if len(dist_matrix[0]) == len(dist_matrix[1]) + 1:
            # This is upper triangular format
            dist_matrix = upper_triangular_to_full(dist_matrix)
    
    n = len(dist_matrix)
    
    # If start_node not specified, try all starting nodes
    if start_node is None:
        best_cost = float('inf')
        best_path = None
        
        for s in range(n):
            cost, path = held_karp(dist_matrix, return_to_start, start_node=s)
            if cost < best_cost:
                best_cost = cost
                best_path = path
        
        return best_cost, best_path
    
    # Solve with specific starting node
    # memo[mask][i] = (min_cost, prev_node) to reach node i with visited set = mask
    memo = {}
    
    # Base case: start from start_node, visit each other node
    for i in range(n):
        if i != start_node:
            memo[(1 << i, i)] = (dist_matrix[start_node][i], start_node)
    
    # Iterate over all subsets of nodes (excluding start_node)
    nodes = [i for i in range(n) if i != start_node]
    
    for subset_size in range(2, n):
        for subset in combinations(nodes, subset_size):
            # Convert subset to bitmask
            mask = 0
            for bit in subset:
                mask |= 1 << bit
            
            # For each node in the subset, try to extend path ending at that node
            for last in subset:
                prev_mask = mask & ~(1 << last)  # Remove last node from mask
                
                min_cost = float('inf')
                min_prev = None
                
                # Try all possible previous nodes
                for prev in subset:
                    if prev == last:
                        continue
                    
                    # Check if we have a path to prev with prev_mask
                    if (prev_mask, prev) in memo:
                        cost = memo[(prev_mask, prev)][0] + dist_matrix[prev][last]
                        if cost < min_cost:
                            min_cost = cost
                            min_prev = prev
                
                if min_prev is not None:
                    memo[(mask, last)] = (min_cost, min_prev)
    
    # Find the minimum cost to visit all nodes (and optionally return to start)
    full_mask = (1 << n) - 1  # All nodes visited
    full_mask &= ~(1 << start_node)  # Exclude starting node from mask
    
    min_cost = float('inf')
    last_node = None
    
    for i in range(n):
        if i != start_node and (full_mask, i) in memo:
            if return_to_start:
                cost = memo[(full_mask, i)][0] + dist_matrix[i][start_node]
            else:
                cost = memo[(full_mask, i)][0]
            
            if cost < min_cost:
                min_cost = cost
                last_node = i
    
    # Reconstruct path
    path = [start_node]
    mask = full_mask
    current = last_node
    
    while current != start_node:
        path.append(current)
        prev = memo[(mask, current)][1]
        mask &= ~(1 << current)
        current = prev
    
    if return_to_start:
        path.append(start_node)  # Return to start
    
    return min_cost, path


def combinations(items, k):
    """Generate all k-combinations of items"""
    if k == 0:
        yield []
        return
    
    for i in range(len(items)):
        for combo in combinations(items[i+1:], k-1):
            yield [items[i]] + combo


def main(puzzle, part_two=False):

    matrix = []
    curr = ''
    with open(puzzle, 'r') as f:
        c = []
        for ln in f:
            l = ln.rstrip('\n')
            s, d = l.split(' = ')
            if s.split(' ')[0] != curr:
                if len(c) > 0: matrix.append(c)
                curr = s.split(' ')[0]
                c = [int(d)]
            else:
                c.append(int(d))
        matrix.append(c)

    if part_two:
        for i in range(len(matrix)):
            for j in range(len(matrix[i])):
                matrix[i][j] *= -1

    min_cost, _ = held_karp(matrix)
    word = "maximum" if part_two else "minimum"
    min_cost *= -1 if part_two else 1
    print(f"The {word} distance is {min_cost}")


    return


if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument("puzzle_path", type=str)
    parser.add_argument("part", type=int)

    args = parser.parse_args()

    main(args.puzzle_path, part_two=args.part==2)