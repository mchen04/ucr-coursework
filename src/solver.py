import heapq
import math # need this for sqrt
import time # need this for timing
import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
from src.node import Node # the node class

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
        state_list[index], state_list[index - 3] = state_list[index - 3], state_list[index] # the actual swap
        return tuple(state_list)
    return None # cant move up

def move_down(state):
    # move 0 down
    index = find_blank(state)
    if index < 6:  # check if not bottom row
        state_list = list(state)
        state_list[index], state_list[index + 3] = state_list[index + 3], state_list[index] # swap
        return tuple(state_list)
    return None # cant move down

def move_left(state):
    # move 0 left
    index = find_blank(state)
    if index % 3 != 0:  # check if not left col
        state_list = list(state)
        state_list[index], state_list[index - 1] = state_list[index - 1], state_list[index] # swap
        return tuple(state_list)
    return None # cant move left

def move_right(state):
    # move 0 right
    index = find_blank(state)
    if index % 3 != 2:  # check if not right col
        state_list = list(state)
        state_list[index], state_list[index + 1] = state_list[index + 1], state_list[index] # swap
        return tuple(state_list)
    return None # cant move right

# Search Algorithms

def solve_ucs(initial_state, goal_state, trace=False):
    # Uniform Cost Search function
    start_node = Node(initial_state, None, 0, 0) # h=0 for ucs
    frontier = [] # this is a priority queue (min-heap)
    heapq.heappush(frontier, start_node)
    explored_set = set() # track states we already visited
    frontier_nodes = {start_node.state: start_node} # track nodes currently in frontier

    nodes_expanded = 0
    max_queue_size = 0

    while frontier: # loop until frontier is empty
        max_queue_size = max(max_queue_size, len(frontier)) # update max queue size

        # Trace Output (if enabled)
        if trace and frontier:
             best_node = frontier[0] # look at the best node
             print(f"\nThe best state to expand with g(n) = {best_node.g_cost} and h(n) = {best_node.h_cost} is...{format_state(best_node.state)}")

        # get the node with lowest g_cost
        current_node = heapq.heappop(frontier)

        # basic checks to skip redundant work
        if current_node.state in explored_set:
             continue
        if current_node.state in frontier_nodes: # make sure we haven't found a better path already
             del frontier_nodes[current_node.state]

        if trace: print("Expanding this node...")
        nodes_expanded += 1

        # Goal Check
        if current_node.state == goal_state:
            return current_node, nodes_expanded, max_queue_size # found 

        # Add to Explored Set
        explored_set.add(current_node.state)

        # Generate Children (expand node)
        for move_func in (move_up, move_down, move_left, move_right):
            child_state = move_func(current_node.state)

            # check if move is okay and we haven't seen state before
            if child_state is not None and child_state not in explored_set:
                g_cost_child = current_node.g_cost + 1 # cost is +1 per move
                child_node = Node(child_state, current_node, g_cost_child, 0) # make the child node

                # add to frontier if it's new or we found a cheaper path to it
                if child_state not in frontier_nodes or g_cost_child < frontier_nodes[child_state].g_cost:
                    heapq.heappush(frontier, child_node)
                    frontier_nodes[child_state] = child_node # track it

    # if we get here, no solution found
    return None, nodes_expanded, max_queue_size

# Heuristic Functions

def heuristic_misplaced(state, goal_state):
    # h1: count tiles not in their final spot (ignore 0)
    count = 0
    for index, tile in enumerate(state):
        if tile != 0 and tile != goal_state[index]: # not blank and wrong pos
            count += 1
    return count

def heuristic_euclidean(state, goal_state):
    # h2: sum of euclidean distances for each tile to its goal spot (ignore 0)
    total_distance = 0
    size = 3 # 3x3 grid assumed
    # pre-calculate goal positions for faster lookup
    goal_positions = {tile: index for index, tile in enumerate(goal_state)}

    for index, tile in enumerate(state):
        if tile != 0: # ignore the blank tile
            goal_index = goal_positions[tile] # where this tile should end up
            # get current row/col
            current_row, current_col = index // size, index % size
            # get goal row/col
            goal_row, goal_col = goal_index // size, goal_index % size
            # calculate distance using formula
            distance = math.sqrt((current_row - goal_row)**2 + (current_col - goal_col)**2)
            total_distance += distance
    return total_distance

# A* Search

def solve_a_star(initial_state, goal_state, heuristic_func, trace=False):
    # A* search function
    h_start = heuristic_func(initial_state, goal_state) # h for start state
    start_node = Node(initial_state, None, 0, h_start)
    frontier = [] # priority queue storing (f_cost, node) tuples
    heapq.heappush(frontier, (start_node.f_cost, start_node))
    explored_set = set() # track visited states
    frontier_nodes = {start_node.state: start_node} # track nodes in frontier

    nodes_expanded = 0
    max_queue_size = 0

    while frontier: # loop until frontier empty
        max_queue_size = max(max_queue_size, len(frontier)) # update max queue size

        # Trace Output (if enabled)
        if trace and frontier:
             best_f, best_node = frontier[0] # peek at best node (lowest f)
             print(f"\nThe best state to expand with g(n) = {best_node.g_cost} and h(n) = {best_node.h_cost:.2f} is...{format_state(best_node.state)}")

        # get node with lowest f_cost
        f_cost_current, current_node = heapq.heappop(frontier)

        # skip if already explored
        if current_node.state in explored_set:
             continue
        # skip if this node is outdated (found better path already)
        if current_node.state not in frontier_nodes or frontier_nodes[current_node.state] != current_node:
             continue

        # okay, we are expanding this node now
        del frontier_nodes[current_node.state] # remove from tracker

        if trace: print("Expanding this node...")
        nodes_expanded += 1

        # Goal Check
        if current_node.state == goal_state:
            return current_node, nodes_expanded, max_queue_size # found 

        # Add to Explored Set
        explored_set.add(current_node.state)

        # Generate Children (expand node)
        for move_func in (move_up, move_down, move_left, move_right):
            child_state = move_func(current_node.state)

            # check if move okay and state not explored
            if child_state is not None and child_state not in explored_set:
                # calculate child costs
                g_cost_child = current_node.g_cost + 1
                h_cost_child = heuristic_func(child_state, goal_state)
                child_node = Node(child_state, current_node, g_cost_child, h_cost_child) # make child node

                # add to frontier if new or better path found (check g_cost)
                if child_state not in frontier_nodes or g_cost_child < frontier_nodes[child_state].g_cost:
                    heapq.heappush(frontier, (child_node.f_cost, child_node)) # push (f, node) tuple
                    frontier_nodes[child_state] = child_node # track it

    # if we get here, no solution found
    return None, nodes_expanded, max_queue_size

# Path Reconstruction

def backtrack_path(goal_node):
    # count steps from goal back to start
    depth = 0
    current = goal_node
    while current is not None and current.parent is not None: # follow parents up
        depth += 1
        current = current.parent
    # handle if start node is the goal node
    if depth == 0 and goal_node is not None and goal_node.parent is None:
        return 0
    return depth

# Main Execution

if __name__ == "__main__":
    goal_state = (1, 2, 3, 4, 5, 6, 7, 8, 0) # the goal board

    # Test Cases from rubric
    puzzles = {
        "Trivial":     (1, 2, 3, 4, 5, 6, 7, 8, 0),
        "Very Easy":   (1, 2, 3, 4, 5, 6, 0, 7, 8),
        "Easy":        (1, 2, 0, 4, 5, 3, 7, 8, 6),
        "Doable":      (0, 1, 2, 4, 5, 3, 7, 8, 6),
        "Oh Boy":      (8, 7, 1, 6, 0, 2, 5, 4, 3),
        "Impossible":  (1, 2, 3, 4, 5, 6, 8, 7, 0), # this one can't be solved
        "Trace Ex":    (1, 0, 3, 4, 2, 6, 7, 5, 8)  # for the demo trace
    }
    puzzle_names = list(puzzles.keys())
    default_puzzle_name = "Very Easy" # default puzzle to use

    # Welcome message
    print("Welcome to Michael & Tabito's 8-Puzzle Solver!")

    # Puzzle Selection
    print('Type "1" to use a default puzzle, or "2" to enter your own puzzle.')
    puzzle_mode = input()

    initial_state = None
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
            print(f"Using custom puzzle: {format_state(initial_state)}")

        except Exception as e: # catch errors if input bad
             print(f"Error reading puzzle: {e}. Using default '{default_puzzle_name}'.")
             initial_state = puzzles[default_puzzle_name]

    # Default case (if mode 1 or custom input failed)
    if initial_state is None:
        # let user pick a default puzzle
        print("\nSelect a default puzzle:")
        for i, name in enumerate(puzzle_names): print(f"{i+1}. {name}")
        try:
            default_idx = puzzle_names.index(default_puzzle_name)
            choice = int(input(f"Enter choice (1-{len(puzzle_names)}) [default: {default_idx+1}]: ") or str(default_idx+1)) # handle empty input
            chosen_name = puzzle_names[choice-1]
            initial_state = puzzles[chosen_name]
            print(f"Using default puzzle: {chosen_name} {format_state(initial_state)}")
        except: # catch invalid choice number etc
            print(f"Invalid choice. Using default: {default_puzzle_name} {format_state(puzzles[default_puzzle_name])}")
            initial_state = puzzles[default_puzzle_name]


    # Algorithm Selection
    print("\nEnter your choice of algorithm")
    print("1. Uniform Cost Search")
    print("2. A* with the Misplaced Tile heuristic")
    print("3. A* with the Euclidean Distance heuristic")
    algorithm_choice = input("Enter choice (1, 2, or 3) [default: 1]: ") or "1" # handle empty input

    # Run the Search
    result_node = None
    nodes_expanded = 0
    max_queue_size = 0
    solver_func = None
    heuristic = None
    trace_enabled = False # only trace A* euclidean for demo

    start_time = time.time() # start the timer

    # figure out which function to call
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
        trace_enabled = True # turn trace on for this one
    else:
        print("\nInvalid choice. Running default (Uniform Cost Search)...")
        algorithm_choice = "1" # force default
        solver_func = solve_ucs

    # Call the solver
    if solver_func == solve_ucs:
         result_node, nodes_expanded, max_queue_size = solver_func(initial_state, goal_state, trace=trace_enabled)
    elif solver_func == solve_a_star:
         result_node, nodes_expanded, max_queue_size = solver_func(initial_state, goal_state, heuristic, trace=trace_enabled)

    end_time = time.time() # stop timer
    elapsed_time = end_time - start_time

    # Display Results
    print("\n--------------------------")
    if result_node:
        # success messages
        goal_depth = backtrack_path(result_node)
        print(f"\nTo solve this problem the search algorithm expanded a total of {nodes_expanded} nodes.")
        print(f"The maximum number of nodes in the queue at any one time: {max_queue_size}.")
        print(f"The depth of the goal node was {goal_depth}.")
    else:
        # failure messages
        print(f"\nFAILURE: No solution found.")
        print(f"The search algorithm expanded a total of {nodes_expanded} nodes.")
        print(f"The maximum number of nodes in the queue at any one time was {max_queue_size}.")

    print(f"Time Elapsed: {elapsed_time:.4f} seconds") # show time taken
    print("--------------------------")