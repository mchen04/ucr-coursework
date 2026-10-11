import heapq
import math  # need this for sqrt
import time  # need this for timing
import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
from src.node import Node  # the node class


# Helper Functions
def find_blank(state):
    # find the 0 tile index
    return state.index(0)


def format_state(state):
    # print the board in good format
    s = [str(x) for x in state]
    return f"\n{s[0]} {s[1]} {s[2]}\n{s[3]} {s[4]} {s[5]}\n{s[6]} {s[7]} {s[8]}"


# Move Functions
# return new state tuple after move, or None if move is bad


def move_up(state):
    # move 0 up
    index = find_blank(state)
    if index > 2:  # check if not top row
        state_list = list(state)
        state_list[index], state_list[index - 3] = state_list[index - 3], state_list[index]  # the actual swap
        return tuple(state_list)
    return None  # cant move up


def move_down(state):
    # move 0 down
    index = find_blank(state)
    if index < 6:  # check if not bottom row
        state_list = list(state)
        state_list[index], state_list[index + 3] = state_list[index + 3], state_list[index]  # swap
        return tuple(state_list)
    return None  # cant move down


def move_left(state):
    # move 0 left
    index = find_blank(state)
    if index % 3 != 0:  # check if not left col
        state_list = list(state)
        state_list[index], state_list[index - 1] = state_list[index - 1], state_list[index]  # swap
        return tuple(state_list)
    return None  # cant move left


def move_right(state):
    # move 0 right
    index = find_blank(state)
    if index % 3 != 2:  # check if not right col
        state_list = list(state)
        state_list[index], state_list[index + 1] = state_list[index + 1], state_list[index]  # swap
        return tuple(state_list)
    return None  # cant move right


# search algorithms


def solve_ucs(initial_state, goal_state, trace=False):
    # uniform cost search function (A* with h=0)
    start_node = Node(initial_state, None, 0, 0)  # h=0 for ucs
    frontier = []  # this is a priority queue (min-heap) storing node objects

    heapq.heappush(frontier, start_node)
    explored_set = set()  # track states we already visited
    frontier_nodes = {start_node.state: start_node}  # track nodes currently in the frontier for replacement

    nodes_expanded = 0
    max_queue_size = 0

    while frontier:  # loop
        max_queue_size = max(max_queue_size, len(frontier))  # update max queue size
        current_node = heapq.heappop(frontier)  # choose a leaf node and remove it from the frontier
        if current_node.state in frontier_nodes and frontier_nodes[current_node.state] == current_node:
            del frontier_nodes[current_node.state]

        if current_node.state == goal_state:
            return current_node, nodes_expanded, max_queue_size  # found solution

        if current_node.state in explored_set:
            continue  # already found a path (possibly longer, but explored)
        explored_set.add(current_node.state)

        if trace:  # trace (if enabled), shows nodes being expanded
            print(f"\nthe best state to expand with g(n) = {current_node.g_cost} and h(n) = {current_node.h_cost:.0f} is...{format_state(current_node.state)}")  # use .0f for h(n) consistency
            print("expanding this node...")

        nodes_expanded += 1  # increment nodes expanded after popping and checking explored

        for move_func in (move_up, move_down, move_left, move_right):  # expand the chosen node, adding the resulting nodes to frontier
            child_state = move_func(current_node.state)

            if child_state is not None and child_state not in explored_set:  # only if child state is valid and not better explored
                g_cost_child = current_node.g_cost + 1  # cost is +1 per move
                child_node = Node(child_state, current_node, g_cost_child, 0)  # make the child node
                # check if child is not in frontier or if new path is cheaper
                if child_state not in frontier_nodes or g_cost_child < frontier_nodes[child_state].g_cost:
                    heapq.heappush(frontier, child_node)
                    frontier_nodes[child_state] = child_node  # update with better node


# Heuristic Functions


def heuristic_misplaced(state, goal_state):
    # h1: count tiles not in their final spot (ignore 0)
    count = 0
    for index, tile in enumerate(state):
        if tile != 0 and tile != goal_state[index]:  # not blank and wrong pos
            count += 1
    return count


def heuristic_euclidean(state, goal_state):
    # h2: sum of euclidean distances for each tile to its goal spot (ignore 0)
    total_distance = 0.0
    size = 3  # 3x3 grid assumed
    # pre-calculate goal positions for faster lookup
    goal_positions = {tile: index for index, tile in enumerate(goal_state)}

    for index, tile in enumerate(state):
        if tile != 0:  # ignore the blank tile
            current_row, current_col = index // size, index % size
            goal_idx = goal_positions[tile]
            goal_row, goal_col = goal_idx // size, goal_idx % size
            distance = math.sqrt((current_row - goal_row)**2 + (current_col - goal_col)**2)  # calculate distance using formula
            total_distance += distance
    return total_distance


# A* search


def solve_a_star(initial_state, goal_state, heuristic_func, trace=False):
    # a* search function
    h_start = heuristic_func(initial_state, goal_state)  # h for start state
    start_node = Node(initial_state, None, 0, h_start)
    frontier = []  # priority queue storing node

    heapq.heappush(frontier, start_node)
    explored_set = set()  # track visited states (store states, not nodes)
    frontier_nodes = {start_node.state: start_node}  # track nodes currently in the frontier for replacement

    nodes_expanded = 0
    max_queue_size = 0

    while frontier:
        max_queue_size = max(max_queue_size, len(frontier))  # update max queue size
        current_node = heapq.heappop(frontier)
        # check if it was already removed by a replacement node found later
        if current_node.state in frontier_nodes and frontier_nodes[current_node.state] == current_node:
            del frontier_nodes[current_node.state]

        # if the node contains a goal state then return the solution
        if current_node.state == goal_state:
            return current_node, nodes_expanded, max_queue_size  # found solution

        # check before adding to explored set to avoid useless checks later
        if current_node.state in explored_set:
            continue  # already found a path (possibly longer, but explored)
        explored_set.add(current_node.state)

        if trace:  # trace output (if enabled) - show node being expanded
            print(f"\nthe best state to expand with g(n) = {current_node.g_cost} and h(n) = {current_node.h_cost:.0f} is...{format_state(current_node.state)}")
            print("expanding this node...")

        nodes_expanded += 1  # increment nodes expanded *after* confirming it's not explored/goal

        # expand the chosen node, adding the resulting nodes to the frontier
        for move_func in (move_up, move_down, move_left, move_right):
            child_state = move_func(current_node.state)

            # only if child state is valid and not already explored
            if child_state is not None and child_state not in explored_set:
                # calculate child costs
                g_cost_child = current_node.g_cost + 1
                h_cost_child = heuristic_func(child_state, goal_state)
                child_node = Node(child_state, current_node, g_cost_child, h_cost_child)  # make child node

                # check if child is not in frontier or if this new path is cheaper
                if child_state not in frontier_nodes or g_cost_child < frontier_nodes[child_state].g_cost:
                    # add to frontier (heapq) and tracking dict
                    heapq.heappush(frontier, child_node)
                    frontier_nodes[child_state] = child_node  # update with better node

    # if the frontier is empty then return failure
    return None, nodes_expanded, max_queue_size


# Path Reconstruction


def backtrack_path(goal_node):
    # count steps (depth) from goal back to start
    depth = 0
    current = goal_node
    # follow parents up, counting moves
    while current is not None and current.parent is not None:
        depth += 1
        current = current.parent

    return depth


# Main Execution


if __name__ == "__main__":
    goal_state = (1, 2, 3, 4, 5, 6, 7, 8, 0)  # the goal board

    # test cases from rubric
    puzzles = {
        "Trivial":     (1, 2, 3, 4, 5, 6, 7, 8, 0),
        "Very Easy":   (1, 2, 3, 4, 5, 6, 0, 7, 8),
        "Easy":        (1, 2, 0, 4, 5, 3, 7, 8, 6),
        "Doable":      (0, 1, 2, 4, 5, 3, 7, 8, 6),
        "Oh Boy":      (8, 7, 1, 6, 0, 2, 5, 4, 3),
        "Impossible":  (1, 2, 3, 4, 5, 6, 8, 7, 0),  # this one can't be solved
        "Trace Ex":    (1, 0, 3, 4, 2, 6, 7, 5, 8)   # for the demo trace
    }
    # define the exact state tuple required for the trace
    trace_required_puzzle_state = (1, 0, 3, 4, 2, 6, 7, 5, 8)

    puzzle_names = list(puzzles.keys())
    default_puzzle_name = "Very Easy"  # default puzzle to use

    # Welcome Message
    print("Welcome to 862369509 & Tabito Student ID 8-Puzzle Solver!")

    # Puzzle Selection
    print('Type "1" to use a default puzzle, or "2" to enter your own puzzle.')
    puzzle_mode = input()

    initial_state = None
    chosen_puzzle_name = ""
    if puzzle_mode == "2":
        # get custom puzzle from user
        print("Enter your puzzle, use a zero (0) to represent the blank space.")
        puzzle_list = []
        try:
            row1_input = input("Enter the first row, use space or tabs between numbers: ")
            puzzle_list.extend([int(x) for x in row1_input.split()])
            row2_input = input("Enter the second row, use space or tabs between numbers: ")
            puzzle_list.extend([int(x) for x in row2_input.split()])
            row3_input = input("Enter the third row, use space or tabs between numbers: ")
            puzzle_list.extend([int(x) for x in row3_input.split()])

            # check if input is valid
            if len(puzzle_list) != 9: raise ValueError("needs 9 numbers")
            if len(set(puzzle_list)) != 9 or not all(0 <= x <= 8 for x in puzzle_list): raise ValueError("needs unique numbers 0-8")

            initial_state = tuple(puzzle_list)
            chosen_puzzle_name = "Custom"
            print(f"Using custom puzzle: {format_state(initial_state)}")

        except Exception as e:  # catch errors if input bad
            print(f"Error reading puzzle: {e}. Using default '{default_puzzle_name}'.")
            chosen_puzzle_name = default_puzzle_name
            initial_state = puzzles[chosen_puzzle_name]

            if initial_state:
                print(f"Using default puzzle: {chosen_puzzle_name} {format_state(initial_state)}")

    # default case (if mode 1 or custom input failed)
    if initial_state is None:
        # let user pick a default puzzle
        print("\nSelect a default puzzle:")
        for i, name in enumerate(puzzle_names): print(f"{i+1}. {name}")
        try:
            default_idx = puzzle_names.index(default_puzzle_name)
            choice_str = input(f"Enter choice (1-{len(puzzle_names)}) [default: {default_idx+1}]: ") or str(default_idx+1)
            choice = int(choice_str)
            if 1 <= choice <= len(puzzle_names):
                chosen_puzzle_name = puzzle_names[choice-1]
                initial_state = puzzles[chosen_puzzle_name]
                print(f"Using default puzzle: {chosen_puzzle_name} {format_state(initial_state)}")
            else:
                raise ValueError("Choice out of range")
        except (ValueError, IndexError, KeyError):
            print(f"Invalid choice or puzzle '{default_puzzle_name}' not found. Using first available default.")

            if puzzle_names:
                chosen_puzzle_name = puzzle_names[0]
                initial_state = puzzles[chosen_puzzle_name]
                print(f"Using default puzzle: {chosen_puzzle_name} {format_state(initial_state)}")
            else:
                print("Error: No default puzzles available.")
                sys.exit(1)  # exit if no puzzle could be loaded

    # Algorithm Selection
    print("\nEnter your choice of algorithm")
    print("1. Uniform Cost Search")
    print("2. A* with the Misplaced Tile heuristic")
    print("3. A* with the Euclidean Distance heuristic")
    algorithm_choice = input("Enter choice (1, 2, or 3) [default: 1]: ") or "1"  # handle empty input

    # Run the Search
    result_node = None
    nodes_expanded = 0
    max_queue_size = 0
    solver_func = None
    heuristic = None
    trace_enabled = False  # enable trace only if A* euclidean is chosen and specific trace puzzle state is used

    start_time = time.time()  # start the timer

    if algorithm_choice == "1":
        print("\nRunning Uniform Cost Search...")
        solver_func = solve_ucs
    elif algorithm_choice == "2":
        print("\nRunning A* with Misplaced Tile Heuristic...")
        solver_func = solve_a_star
        heuristic = heuristic_misplaced
    elif algorithm_choice == "3":
        print("\nRunning A* with Euclidean Distance Heuristic...")
        solver_func = solve_a_star
        heuristic = heuristic_euclidean
        # only enable trace if it's A* euclidean and the specific puzzle
        if initial_state == trace_required_puzzle_state:
            trace_enabled = True
            print("Trace enabled for the required Gradescope puzzle.")
    else:
        print("\nInvalid choice. Running default (Uniform Cost Search)...")
        algorithm_choice = "1"
        solver_func = solve_ucs

    # Call the Solver
    if solver_func:
        if solver_func == solve_ucs:
            # pass trace flag to UCS
            result_node, nodes_expanded, max_queue_size = solver_func(initial_state, goal_state, trace=trace_enabled)
        elif solver_func == solve_a_star and heuristic:
            # pass trace flag and heuristic to A*
            result_node, nodes_expanded, max_queue_size = solver_func(initial_state, goal_state, heuristic, trace=trace_enabled)
        else:
            print("Error: Solver configuration issue.")
    else:
        print("Error: Solver function not determined.")

    end_time = time.time()
    elapsed_time = end_time - start_time

    # Display Results
    print("--------------------------")
    if result_node:
        print("\nGoal!!!")
        goal_depth = backtrack_path(result_node)
        print(f"\nto solve this problem the search algorithm expanded a total of {nodes_expanded} nodes.")
        print(f"the maximum number of nodes in the queue at any one time: {max_queue_size}.")
        print(f"the depth of the goal node was {goal_depth}.")
    else:
        print(f"\nfailure: no solution found.")
        print(f"the search algorithm expanded a total of {nodes_expanded} nodes.")
        print(f"the maximum number of nodes in the queue at any one time was {max_queue_size}.")

    print("--------------------------")
