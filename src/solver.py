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

    while frontier:
        current_node = heapq.heappop(frontier)
        frontier_states.discard(current_node.state)

        if current_node.state == goal_state:
            return current_node

        explored_set.add(current_node.state)

        for move_func in (move_up, move_down, move_left, move_right):
            child_state = move_func(current_node.state)
            if child_state is not None and child_state not in explored_set and child_state not in frontier_states:
                child_node = Node(child_state, current_node, current_node.g_cost + 1)
                heapq.heappush(frontier, child_node)
                frontier_states.add(child_node.state)

if __name__ == "__main__":
    initial_state = (1, 2, 3, 4, 5, 6, 0, 7, 8)
    goal_state = (1, 2, 3, 4, 5, 6, 7, 8, 0)

    print("Initial state:", initial_state)
    result = solve_ucs(initial_state, goal_state)

    if result:
        print("successful")
    else:
        print("unsuccessful")