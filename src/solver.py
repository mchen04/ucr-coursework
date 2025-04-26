import heapq
from node import Node

def find_blank(state):
    return state.index(0)

def move_up(state):
    index = find_blank(state)
    if index not in (0, 1, 2):  # not in top row
        state_list = list(state)
        state_list[index], state_list[index - 3] = state_list[index - 3], state_list[index]
        return tuple(state_list)
    return None

def move_down(state):
    index = find_blank(state)
    if index not in (6, 7, 8):  # not in bottom row
        state_list = list(state)
        state_list[index], state_list[index + 3] = state_list[index + 3], state_list[index]
        return tuple(state_list)
    return None

def move_left(state):
    index = find_blank(state)
    if index % 3 != 0:  # not in left column
        state_list = list(state)
        state_list[index], state_list[index - 1] = state_list[index - 1], state_list[index]
        return tuple(state_list)
    return None

def move_right(state):
    index = find_blank(state)
    if index % 3 != 2:  # not in right column
        state_list = list(state)
        state_list[index], state_list[index + 1] = state_list[index + 1], state_list[index]
        return tuple(state_list)
    return None

def solve_ucs(initial_state, goal_state):
    start_node = Node(initial_state, None, 0)
    frontier = []
    heapq.heappush(frontier, start_node)
    explored_set = set()
    frontier_states = set()
    frontier_states.add(start_node.state)
    nodes_expanded = 0
    max_queue_size = 0

    while frontier:
        max_queue_size = max(max_queue_size, len(frontier))

        current_node = heapq.heappop(frontier)
        print(f"Expanding node with g={current_node.g_cost}, state={current_node.state}")
        nodes_expanded += 1
        frontier_states.discard(current_node.state)

        if current_node.state == goal_state:
            return current_node, nodes_expanded, max_queue_size

        explored_set.add(current_node.state)

        for move_func in (move_up, move_down, move_left, move_right):
            child_state = move_func(current_node.state)
            if child_state is not None and child_state not in explored_set and child_state not in frontier_states:
                child_node = Node(child_state, current_node, current_node.g_cost + 1)
                heapq.heappush(frontier, child_node)
                frontier_states.add(child_node.state)

    return None, nodes_expanded, max_queue_size


def backtrack_path(goal_node): ## backtrack from goal node to find path
    steps = 0
    current = goal_node
    while current.parent is not None:
        steps += 1
        current = current.parent
    return steps


if __name__ == "__main__":
    goal_state = (1, 2, 3, 4, 5, 6, 7, 8, 0)
    default_puzzle = (1, 2, 3, 4, 5, 6, 0, 7, 8)

    print("8-Puzzle Solver")

    print("\nPuzzles:")
    print("1. Default")
    print("2. Custom")
    puzzle_choice = input("Choose (1 or 2): ")

    initial_state = None
    if puzzle_choice == "1":
        initial_state = default_puzzle
        print("Using default:", initial_state)
    elif puzzle_choice == "2":
        print("\nEnter custom puzzle (space separated nums, 0 for blank):")
        puzzle_list = []
        try:
            row1 = input("Row 1: ")
            puzzle_list.extend([int(x) for x in row1.split()])
            row2 = input("Row 2: ")
            puzzle_list.extend([int(x) for x in row2.split()])
            row3 = input("Row 3: ")
            puzzle_list.extend([int(x) for x in row3.split()])

            if len(puzzle_list) != 9:
                 raise ValueError("Puzzle must have exactly 9 numbers.")

            initial_state = tuple(puzzle_list)
            print("Using custom puzzle:", initial_state)

        except ValueError:
             print("Invalid input format. Using default puzzle.")
             initial_state = default_puzzle

    else:
        initial_state = default_puzzle
        print("Invalid choice. Using default puzzle:", initial_state)


    print("\nRunning Uniform Cost Search...")
    result_node, nodes_expanded, max_queue_size = solve_ucs(initial_state, goal_state)

    if result_node:
        steps = backtrack_path(result_node)
        print("successful")
        print("nodes expanded: ", nodes_expanded)
        print("max queue: ", max_queue_size)
        print("steps until solved: ", steps)
    else:
        print("unsuccessful")
        print("nodes expanded: ", nodes_expanded)
        print("max queue during search: ", max_queue_size)
