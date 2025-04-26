class Node:
    def __init__(self, state, parent, g_cost, h_cost=0, f_cost=0):
        self.state = state
        self.parent = parent
        self.g_cost = g_cost
        self.h_cost = h_cost
        self.f_cost = f_cost

    def __lt__(self, other):
        return self.g_cost < other.g_cost  ## compare nodes by cost 