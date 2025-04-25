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
    if index % 3 != 0:  # not in right column
        state_list = list(state)
        state_list[index], state_list[index - 1] = state_list[index - 1], state_list[index]  
        return tuple(state_list)
    return None

initial_state = [1, 2, 3, 4, 5, 6, 7, 8, 0]

if __name__ == "__main__":
    print("Initial state:", initial_state)
    print("Up:   ", move_up(initial_state))
    print("Down: ", move_down(initial_state))
    print("Left: ", move_left(initial_state))
    print("Right:", move_right(initial_state))