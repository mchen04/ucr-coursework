class Node:
    def __init__(self, state, parent, g_cost):
        self.state = state
        self.parent = parent  
        self.g_cost = g_cost

    def __lt__(self, other):
        return self.g_cost < other.g_cost  ## compare nodes by cost 