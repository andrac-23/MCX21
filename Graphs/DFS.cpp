#include <bits/stdc++.h>

using namespace std;

class Graph {
public:
        Graph(int nodes, int edges) {
            this->adjacency_list.resize(nodes);
            this->nodes = nodes;
            this->edges = edges;
        }

        void Read_Graph() {
            for (int i = 0; i != edges; i++) {
                int node_a, node_b;
                cin >> node_a >> node_b;
                adjacency_list[node_a].push_back(node_b);
                // Undirected Graph
                // adjacency_list[node_b].push_back(node_a);
            }
        }

        void DFS();

private:

        void DFS_Algo(vector<bool> &visited, vector<int> &discovery, vector<int> &finish, int curr_node, int &time);

        vector<vector<int>> adjacency_list;
        int nodes;
        int edges;
};

bool is_Disjoint(int current_node, int next_node) {
    return((current_node > next_node));
}

void Graph::DFS() {
    vector<bool> visited(nodes);
    vector<int> discovery(nodes);
    vector<int> finish(nodes);

    // Global variable
    int time = 0;
    for (int i = 0; i != nodes; i++) {
        if (!visited[i]) {
            DFS_Algo(visited, discovery, finish, i, time);
        }
    }
}

void Graph::DFS_Algo(vector<bool> &visited, vector<int> &discovery, vector<int> &finish, int curr_node, int &time) {
    /* Classify edges:

      - Tree edges
      - Forward edges
      - Back edges
      - Cross edges

    */
    time++;
    visited[curr_node] = 1;
    discovery[curr_node] = time;
    for (int i = 0; i != (int) adjacency_list[curr_node].size(); i++) {
        // Next node
        int next_node = adjacency_list[curr_node][i];
        if (!visited[next_node]) {
            // Create Tree Edge
            cout << "Tree Edge " << curr_node << next_node << "\n";

            DFS_Algo(visited, discovery, finish, next_node, time);
        }
        else {
            if (discovery[next_node] < discovery[curr_node] && finish[next_node]) {
                // Cross edge, disjoint
                cout << "Cross Edge " << curr_node << next_node << "\n";
            }
            else {
                if (discovery[next_node] < discovery[curr_node]) {
                    // Back edge
                    cout << "Back Edge " << curr_node << next_node << "\n";
                }
                else {
                    // Forward edge
                    cout << "Forward Edge " << curr_node << next_node << "\n";
                }
            }
        }
    }
    time++;
    finish[curr_node] = time;
}

int main() {
    int nodes, edges;
    cin >> nodes >> edges;
    Graph new_graph = Graph(nodes, edges);
    new_graph.Read_Graph();

    new_graph.DFS();

    return 0;
}
