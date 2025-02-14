
import argparse
import logging, sys
import pdb

from collections import deque

class TopologicalSorter:
    def __init__(self, graph_representation="edges"):  # Default to edges
        self.graph_type = graph_representation
        self.graph = None  # Graph will be set later
        self.visited = None
        self.stack = None

    def sort(self, graph_data):  # Generic sort method
        self.graph = graph_data
        pdb.set_trace()
        node_count = len(self.graph)
        if self.graph_type == "edges":
            node_count = self._get_node_count()
        self.visited = [False] * node_count 
        self.stack = deque()

        incount = [0] * node_count
        # find nodes w/ no dependencies
        # that is, no incoming edges
        for edge in self.graph:
            incount[edge[1]] = incount[edge[1]] + 1

        while True:
            node = 0
            appended = False
            while True:
                if incount[node] == 0 and not node in self.stack:
                    self.stack.append(node)
                    appended = True
                    edge = 0
                    while len(self.graph) > 0:
                        if self.graph[edge][0] == node:
                            incount[self.graph[edge][1]] -= 1
                            self.graph.pop(edge)
                        else:
                            edge = edge + 1
                        if edge == len(self.graph):
                            break
                node = node + 1
                if node == node_count:
                    break
            if node_count == len(self.stack) or not appended:
                break

        if not appended:
            print("CYCLE")
                    


        return list(self.stack)  # Return topological order as a list

    def _build_adjacency_list(self):
        # trick way to figure out number of nodes from number of edges
        # "inner max" is for each edge
        # adj_list = [() for _ in range(max(max(edge) for edge in self.graph) + 1)] if self.graph else [] # Handle empty graph case
        # expand for comprehension
        adj_list = []
        tempmax = 0
        if self.graph:
            for edge in self.graph:
                if max(edge) > tempmax:
                    tempmax = max(edge)
            adj_list = [() for _ in range(tempmax + 1)]
        for u, v in self.graph:
            adj_list[u] = adj_list[u] + (v,)
        self.graph = adj_list
        self.graph_type = "adjacency" # Update to adjacency list type

    def _get_node_count(self):
        adj_list = []
        tempmax = 0
        if self.graph:
            for edge in self.graph:
                if max(edge) > tempmax:
                    tempmax = max(edge)
            adj_list = [() for _ in range(tempmax + 1)]
        for u, v in self.graph:
            adj_list[u] = adj_list[u] + (v,)
        return len(adj_list)




if __name__ == "__main__":
    edges = [(2, 3), (3, 1), (4, 0), (4, 1), (5, 0), (5, 2)]
    adjacency = [(), (), (3,), (1,), (0, 1), (0, 2)]

    # Using edges:
    sorter_edges = TopologicalSorter(graph_representation="edges")
    topological_order_edges = sorter_edges.sort(edges)
    print("Topological Sort (Edges):", topological_order_edges)

    edges = [(0,1), (1,2), (3,2), (3,4)]

    sorter_edges = TopologicalSorter(graph_representation="edges")
    topological_order_edges = sorter_edges.sort(edges)
    print("Topological Sort (Edges):", topological_order_edges)

    # CYCLE
    edges = [(0,1), (1,2), (2,0), (3,2), (3,4)]

    sorter_edges = TopologicalSorter(graph_representation="edges")
    topological_order_edges = sorter_edges.sort(edges)
    print("Topological Sort (Edges):", topological_order_edges)

    edges = [(0, 1), (1, 2), (2, 3), (4, 5), (5, 1), (5, 2)]

    sorter_edges = TopologicalSorter(graph_representation="edges")
    topological_order_edges = sorter_edges.sort(edges)
    print("Topological Sort (Edges):", topological_order_edges)

    # Using adjacency list:
    # sorter_adj = TopologicalSorter(graph_representation="adjacency")
    # topological_order_adj = sorter_adj.sort(adjacency)
    # print("Topological Sort (Adjacency List):", topological_order_adj)

    # Example of using lambda to define graph data:
    graph_data = lambda: [(0, 1), (1, 2), (2, 3)]
    sorter_lambda = TopologicalSorter(graph_representation="edges")
    topological_order_lambda = sorter_lambda.sort(graph_data()) # Note the call to graph_data()
    print("Topological Sort (Lambda):", topological_order_lambda)