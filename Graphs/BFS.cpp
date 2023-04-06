//#include <bits/stdc++.h>

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

class Graph {
public:
        Graph(int nodes) {
            this->length = nodes;
            adjacency_list.resize(nodes);
        }

        void Read_Graph(int edges) {
            // Read Adjacency List; Nodes are named (0...n-1)
            for (int i = 0; i < edges; i++) {
                int node_a; cin >> node_a;
                int node_b; cin >> node_b;
                adjacency_list[node_a].push_back(node_b);
                adjacency_list[node_b].push_back(node_a);
            }
        }
        // Fills Balance_Tree and Distance Vector
        void BFS(int s, vector<int> &balance_tree, vector<int> &dist) {
            // All nodes start with visited = 0
            vector<int> visited(length, 0);
            queue<int> to_visit;
            // Init nodes
            for (int i = 0; i < length; i++) {
                dist[i] = -1;
                balance_tree[i] = -1;
            }
            dist[s] = 0;

            to_visit.push(s);
            while(!to_visit.empty()) {
                int current_node = to_visit.front();
                to_visit.pop();
                for (auto node : adjacency_list[current_node]) {
                    if (!visited[node]) {
                        // Process
                        visited[node] = 1;
                        dist[node] = dist[current_node] + 1;
                        balance_tree[node] = current_node;
                        // To visit
                        to_visit.push(node);
                    }
                }
                visited[current_node] = 1;
            }
        }

private:
        vector<vector<int>> adjacency_list;
        int length;

};

int main() {

    int nodes; cin >> nodes;
    Graph test = Graph(nodes);
    int edges; cin >> edges;
    test.Read_Graph(edges);

    vector<int> dist(nodes);
    vector<int> balance_tree(nodes);

    test.BFS(1, balance_tree, dist);

    for (auto x : dist) {
        cout << x << " ";
    }
    cout << "\n";

    for (auto x : balance_tree) {
        cout << x << " ";
    }
    cout << "\n";

    return 0;
}
