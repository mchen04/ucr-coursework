class Node:
    def __init__(self, state, parent, g_cost, h_cost=0, f_cost=0):
        self.state = state
        self.parent = parent
        self.g_cost = g_cost
        self.h_cost = h_cost
        self.f_cost = f_cost

    def __lt__(self, other):
        if self.f_cost == other.f_cost:
            return self.h_cost < other.h_cost
        return self.f_cost < other.f_cost