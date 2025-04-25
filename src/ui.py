from solver import find_blank, solve_ucs, backtrack_path
if __name__ == "__main__":
    initial_state = (1, 2, 3,
                     4, 5, 6,
                     0, 7, 8)

    goal_state = (1, 2, 3,
                  4, 5, 6,
                  7, 8, 0)

    print("Initial state:", initial_state)
    
    print("Choose a search algorithm:")
    print("1. Uniform Cost Search")
    print("2. A* with Misplaced Tile heuristic")
    print("3. A* with Euclidean Distance heuristic")

    choice = input("Enter your choice 1, 2, 3: ")

    if choice == '1':
        print("\nYou selected Uniform Cost Search.")
        result_node, nodes_expanded, max_queue_size = solve_ucs(initial_state, goal_state)
    elif choice == '2':
        print("A* with Misplaced Tile heuristic.")
        result_node, nodes_expanded, max_queue_size = solve_ucs(initial_state, goal_state)
    elif choice == '3':
        print("A* with Euclidean Distance heuristic.")
        result_node, nodes_expanded, max_queue_size = solve_ucs(initial_state, goal_state)
    else:
        print("Invalid choice.")
        exit()
        
    if result_node:
        steps = backtrack_path(result_node)
        print("successful")
        print("nodes expanded: ",nodes_expanded)
        print("max queue: ", max_queue_size)
        print("steps until solved: " ,steps)
    else:
        print("unsuccessful")