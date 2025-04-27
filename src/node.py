import math

class Node:
    # node for the search tree
    def __init__(self, state, parent, g_cost, h_cost=0):
        self.state = state
        self.parent = parent # parent node pointer
        self.g_cost = g_cost # cost g
        self.h_cost = h_cost # cost h

    # needed for the priority queue (heapq)
    def __lt__(self, other):
        # compare g_cost if UCS, or maybe h_cost for A* tiebreak
        if hasattr(self, 'f_cost') and hasattr(other, 'f_cost'):
             if self.f_cost != other.f_cost:
                 return self.f_cost < other.f_cost
        # default compare g
        return self.g_cost < other.g_cost

    # f_cost = g + h
    @property
    def f_cost(self):
        return self.g_cost + self.h_cost