
# topological sort
# input edges as a list of 2-tuples
# two implementations: DFS (recursive) and BFS/Kahn's
#
# DFS
# initialize visited nodes array
# initialize stack
# loop through unvisited nodes
#   DFS kernel
#   keep track of visited nodee
#   push deepest node onto a stack
# stack pops are in topological order

import argparse
import logging, sys
import pdb

# represent input as list of edges
edges = [
    (2,3),
    (3,1),
    (4,0),
    (4,1),
    (5,0),
    (5,2)
]

# represent input as adjacency list
adjacency = [
    (),
    (),
    (3,),
    (1,),
    (0,1),
    (0,2)
]

def toposort_dfs(node_stack, visited, current_node):
    visited[current_node] = True
    for edge in edges:
        if edge[0] == current_node and not visited[edge[1]]:
            toposort_dfs(node_stack, visited, edge[1])
    node_stack.append(current_node)

def toposort():
    node_stack = []
    visited_nodes = []
    max_node = 0
    for edge in edges:
        for node in edge:
            if node > max_node:
                max_node = node
    print(f"max_node = {max_node}")

    for i in range(max_node+1):
        visited_nodes.append(False)
    for node in range(max_node+1):
        if not visited_nodes[node]:
            toposort_dfs(node_stack, visited_nodes, node)

    the_output(node_stack)

def toposort_dfs_adj(node_stack, visited, current_node):
    print(f"toposort_dfs_adj: {current_node}")
    visited[current_node] = True
    for node in adjacency[current_node]:
        print(f"toposort_dfs_adj: {node}")
        if not visited[node]:
            toposort_dfs_adj(node_stack, visited, node)
    node_stack.append(current_node)

def toposort_adj():
    node_stack = []
    visited_nodes = []

    for i in range(len(adjacency)):
        visited_nodes.append(False)
    for node in range(len(adjacency)):
        if not visited_nodes[node]:
            toposort_dfs_adj(node_stack, visited_nodes, node)

    the_output(node_stack)

def the_output(a_stack):
    templen = len(a_stack)
    print(f"len(stack) = {templen}")
    for i in range(templen):
        print(a_stack.pop())


if __name__ == "__main__":
    toposort()
    toposort_adj()


