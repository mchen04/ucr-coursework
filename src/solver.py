def find_blank(state):
    return state.index(0)


initial_state = [1, 2, 3, 4, 5, 6, 7, 8, 0]

if __name__ == "__main__":
    print("Index:", find_blank(initial_state))