# 8-Puzzle Search

Project 1 for CS 170, Introduction to AI, at UC Riverside.

The program solves the 8-puzzle with three search algorithms and reports the cost of each one:

- Uniform Cost Search
- A* with the Misplaced Tile heuristic
- A* with the Euclidean Distance heuristic

All three share the same graph search loop. Uniform Cost Search is A* with `h(n) = 0`. Each move costs 1.

## Run

```bash
python3 src/solver.py
```

The program asks for a puzzle, then for an algorithm. Choose a built-in puzzle or type your own three rows. Use `0` for the blank tile.

It prints the number of nodes expanded, the maximum queue size, and the depth of the goal node.

## Benchmark

```bash
python3 test/test.py
```

This runs all three algorithms on every built-in puzzle and plots nodes expanded, solution depth, and maximum queue size. It needs `matplotlib`.

## Results

Nodes expanded, by puzzle:

| Puzzle    | Depth | UCS   | Misplaced Tile | Euclidean |
| --------- | ----- | ----- | -------------- | --------- |
| Trivial   | 0     | 0     | 0              | 0         |
| Very Easy | 2     | 5     | 2              | 2         |
| Easy      | 2     | 3     | 2              | 2         |
| Doable    | 4     | 28    | 4              | 4         |
| Oh Boy    | 22    | 85524 | 9121           | 1067      |

All three find the same optimal depth, so both heuristics are admissible. The gap only matters on hard puzzles. On "Oh Boy", the Misplaced Tile heuristic expands about 9x fewer nodes than Uniform Cost Search, and Euclidean Distance expands about 80x fewer. Euclidean Distance is the better heuristic because it measures how far each tile must travel, not just whether it is wrong.

The "Impossible" puzzle has no solution. The search exhausts the frontier and reports failure.
