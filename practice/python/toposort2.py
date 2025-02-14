
from collections import deque

class TopologicalSorter:
    def __init__(self, graph_representation="edges"):  # Default to edges
        self.graph_type = graph_representation
        self.graph = None  # Graph will be set later
        self.visited = None
        self.stack = None

    def sort(self, graph_data):  # Generic sort method
        self.graph = graph_data
        if self.graph_type == "edges":
            self._build_adjacency_list() # Build adjacency list if input is edges
        # self.visited = [False] * len(self.graph) if self.graph_type == "adjacency" else [False] * (max(max(edge) for edge in self.graph) + 1) if self.graph else [] # Handle empty graph case
        self.visited = [False] * len(self.graph) 
        self.stack = deque()

        for node in range(len(self.visited)):
            if not self.visited[node]:
                self._dfs(node)  # Call recursive DFS

        return list(self.stack)  # Return topological order as a list

    def _build_adjacency_list(self):
        # trick way to figure out number of nodes from number of edges
        # "inner max" is for each edge
        adj_list = [() for _ in range(max(max(edge) for edge in self.graph) + 1)] if self.graph else [] # Handle empty graph case
        for u, v in self.graph:
            adj_list[u] = adj_list[u] + (v,)
        self.graph = adj_list
        self.graph_type = "adjacency" # Update to adjacency list type

    def _dfs(self, node):
        self.visited[node] = True
        # for neighbor in self.graph[node] if self.graph_type == "adjacency" else (v for u, v in self.graph if u == node):
        for neighbor in self.graph[node]:
            if not self.visited[neighbor]:
                self._dfs(neighbor)
        self.stack.appendleft(node)  # Add to the left for correct order



if __name__ == "__main__":
    edges = [(2, 3), (3, 1), (4, 0), (4, 1), (5, 0), (5, 2)]
    adjacency = [(), (), (3,), (1,), (0, 1), (0, 2)]

    # Using edges:
    sorter_edges = TopologicalSorter(graph_representation="edges")
    topological_order_edges = sorter_edges.sort(edges)
    print("Topological Sort (Edges):", topological_order_edges)

    # Using adjacency list:
    sorter_adj = TopologicalSorter(graph_representation="adjacency")
    topological_order_adj = sorter_adj.sort(adjacency)
    print("Topological Sort (Adjacency List):", topological_order_adj)

    # Example of using lambda to define graph data:
    graph_data = lambda: [(0, 1), (1, 2), (2, 3)]
    sorter_lambda = TopologicalSorter(graph_representation="edges")
    topological_order_lambda = sorter_lambda.sort(graph_data()) # Note the call to graph_data()
    print("Topological Sort (Lambda):", topological_order_lambda)