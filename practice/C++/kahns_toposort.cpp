
// Including necessary header file
#include <bits/stdc++.h>
using namespace std;

// Function to return list containing vertices in
// Topological order.
// adjacency list input
vector<int> topologicalSort(vector<vector<int>> &adj,
                            int V)
{
    // Vector to store indegree of each vertex
    auto localV = adj.size();
    cout << "localV = " << localV << endl;

    vector<int> indegree(V);
    for (int i = 0; i < V; i++)
    {
        for (auto it : adj[i])
        {
            indegree[it]++;
        }
    }

    // Queue to store vertices with indegree 0
    queue<int> q;
    for (int i = 0; i < V; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }
    vector<int> result;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        result.push_back(node);

        // Decrease indegree of adjacent vertices as the
        // current node is in topological order
        for (auto it : adj[node])
        {
            indegree[it]--;

            // If indegree becomes 0, push it to the queue
            if (indegree[it] == 0)
                q.push(it);
        }
    }

    // Check for cycle
    if (result.size() != V)
    {
        cout << "Graph contains cycle!" << endl;
        return {};
    }

    return result;
}

// edge list input
vector<int> topologicalSortEdges(vector<vector<int>> &edges)
{
    // find number of nodes
    unsigned maxnode = 0;
    for (auto edge : edges)
    {
        if (edge[0] > maxnode)
        {
            maxnode = edge[0];
        }
        if (edge[1] > maxnode)
        {
            maxnode = edge[1];
        }
    }
    unsigned num_nodes = maxnode + 1;
    cout << "number of nodes = " << num_nodes << endl;

    // init queue of independent nodes
    // first, intermediate vector of counts
    vector<int> incoming(num_nodes, 0);
    for (auto edge : edges)
    {
        incoming[edge[1]]++;
    }
    for (auto c : incoming) {
        cout << "incoming count = " << c << endl;
    }

    queue<int> q;

    while (true)
    {
        // we should push a node onto the ouput queue each time,
        // else there's a cycle
        bool pushed = false;
        // loop over nodes
        unsigned node = 0;
        while (true)
        {
            if (0 == incoming[node])
            {
                // hack
                incoming[node] = -1;
                q.push(node);
                pushed = true;
                cout << "pushed " << node << endl;
                // remove edges
                unsigned edge = 0;
                while (true)
                {
                    // check for marker
                    if (-1 == edges[edge][0]) {
                    }
                    else if (edges[edge][0] == node)
                    {
                        incoming[edges[edge][1]]--;
                        // edges.pop(edge);
                        // mark the edge as being removed
                        edges[edge][0] = -1;
                    }
                    // else
                    {
                        edge++;
                    }
                    if (edge == edges.size())
                    {
                        break;
                    }
                }
            }
            node++;
            // cout << "node: " << node << " size: " << incoming.size() << endl;
            if (node == incoming.size())
            {
                break;
            }
        }
        if (!pushed || q.size() == incoming.size()) {
            break;
        }
    }

    return edges[0];
}

int main()
{
    /*
        0 --> 1 --> 2 --> 3
              ^     ^
              |     |
        4 --> 5 ----

     */
    // Number of nodes
    int n = 6;

    // Edges
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {4, 5}, {5, 1}, {5, 2}};

    // Graph represented as an adjacency list:
    // index is node and inner vector holds dependent nodes
    vector<vector<int>> adj(n);

    // Constructing adjacency list
    for (auto i : edges)
    {
        adj[i[0]].push_back(i[1]);
    }

    // Performing topological sort
    cout << "Topological sorting of the graph: ";
    // shouldn't need n below
    vector<int> result = topologicalSort(adj, n);

    // Displaying result
    for (auto i : result)
    {
        cout << i << " ";
    }

    cout << endl;

    cout << "Topological sorting of the graph using edges: ";
    // shouldn't need n below
    result = topologicalSortEdges(edges);

    // Displaying result
    // for (auto i : result) {
    //     cout << i << " ";
    // }

    cout << endl;

    return 0;
}
