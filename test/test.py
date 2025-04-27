import sys
import os
import matplotlib.pyplot as plt

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

from src.solver import solve_ucs, solve_a_star, heuristic_misplaced, heuristic_euclidean, backtrack_path

# Define goal state
GOAL_STATE = (1, 2, 3, 4, 5, 6, 7, 8, 0)

# Define puzzles
PUZZLES = {
    "Trivial":     (1, 2, 3, 4, 5, 6, 7, 8, 0),
    "Very Easy":   (1, 2, 3, 4, 5, 6, 7, 0, 8),
    "Easy":        (1, 2, 0, 4, 5, 3, 7, 8, 6),
    "Doable":      (0, 1, 2, 4, 5, 3, 7, 8, 6),
    "Oh Boy":      (8, 7, 1, 6, 0, 2, 5, 4, 3),
    "Impossible":  (1, 2, 3, 4, 5, 6, 8, 7, 0)
}

# Result storage
nodes_expanded_data = {
    "Uniform Cost Search": [],
    "A* Misplaced Tile": [],
    "A* Euclidean Distance": []
}

steps_data = {
    "Uniform Cost Search": [],
    "A* Misplaced Tile": [],
    "A* Euclidean Distance": []
}

queue_size_data = {
    "Uniform Cost Search": [],
    "A* Misplaced Tile": [],
    "A* Euclidean Distance": []
}

def run_tests():
    for puzzle_name, puzzle in PUZZLES.items():
        print(f"Testing {puzzle_name}")

        # Uniform Cost Search
        print("Running Uniform Cost Search")
        result_node, nodes_expanded, max_queue_size = solve_ucs(puzzle, GOAL_STATE)
        steps = backtrack_path(result_node) if result_node else None
        report_result(result_node)
        record_result("Uniform Cost Search", nodes_expanded, steps, max_queue_size)

        # A* with Misplaced Tile
        print("Running A* with Misplaced Tile heuristic")
        result_node, nodes_expanded, max_queue_size = solve_a_star(puzzle, GOAL_STATE, heuristic_misplaced)
        steps = backtrack_path(result_node) if result_node else None
        report_result(result_node)
        record_result("A* Misplaced Tile", nodes_expanded, steps, max_queue_size)

        # A* with Euclidean Distance
        print("Running A* with Euclidean Distance heuristic")
        result_node, nodes_expanded, max_queue_size = solve_a_star(puzzle, GOAL_STATE, heuristic_euclidean)
        steps = backtrack_path(result_node) if result_node else None
        report_result(result_node )
        record_result("A* Euclidean Distance", nodes_expanded, steps, max_queue_size)

        print("-" * 40)

def report_result(result_node):
    if result_node is None:
        print("Failed to solve")
    else:
        print("Solved")

def record_result(algorithm, nodes_expanded, steps, queue_size):
    nodes_expanded_data[algorithm].append(nodes_expanded)
    steps_data[algorithm].append(steps)
    queue_size_data[algorithm].append(queue_size)

def plot_graph(metric_data, title, puzzles):
    plt.figure()
    for algo_name, values in metric_data.items():
        plt.plot(puzzles, values, marker='o', label=algo_name)
    plt.title(title)
    plt.xlabel("Puzzle")
    plt.ylabel(title)
    plt.xticks(rotation=45)
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    run_tests()

    puzzles = list(PUZZLES.keys())

    plot_graph(nodes_expanded_data, "Nodes Expanded", puzzles)
    plot_graph(steps_data, "Steps to Completion", puzzles)
    plot_graph(queue_size_data, "Max Queue Size", puzzles)