## Running from this collection

From the collection root, enter `projects/01-eight-puzzle-search`, then use the original commands below. The solver needs only the Python standard library (checked with Python 3.12).

For the optional benchmark's Matplotlib dependency:

```bash
python3 -m venv .venv
source .venv/bin/activate
python -m pip install -r requirements-benchmark.txt
python test/test.py
```

The benchmark's existing unsolvable-UCS failure is preserved and documented below. No runtime behavior was changed during consolidation.

---

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

Note: the script stops with a `TypeError` when it reaches the "Impossible" puzzle, so it does not currently render the plot. See Known issue below.

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

The table covers the five solvable puzzles. The "Impossible" puzzle is unsolvable, so no search can return a path.

## Known issue

`solve_ucs` in `src/solver.py` has no return statement after its `while frontier:` loop. On an unsolvable puzzle the loop ends, the function implicitly returns `None`, and the caller crashes:

```
TypeError: cannot unpack non-iterable NoneType object
  solver.py:341
```

`solve_a_star` handles this correctly with `return None, nodes_expanded, max_queue_size`. Adding the same line to the end of `solve_ucs` fixes both the solver and `test/test.py`.

The built-in "Very Easy" puzzle also differs between the two files: `src/solver.py` uses a depth-2 state, `test/test.py` a depth-1 state. The table above reflects `src/solver.py`.
