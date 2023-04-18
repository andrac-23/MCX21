#include <bits/stdc++.h>

using namespace std;

/*

  Only for Directed Acyclic Graphs

*/

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
            }
        }

        void Topological_Sort();

private:
        void Topological_Sort_Algo(int curr_node, vector<bool> &visited, deque<int> &result);

        vector<vector<int>> adjacency_list;
        int nodes;
        int edges;
};


void Graph::Topological_Sort_Algo(int curr_node, vector<bool> &visited, deque<int> &result) {
    visited[curr_node] = true;

    for (int i = 0; i != (int) adjacency_list[curr_node].size(); i++) {
        int next_node = adjacency_list[curr_node][i];
        if (!visited[next_node]) {
            Topological_Sort_Algo(next_node, visited, result);
        }
    }

    result.push_front(curr_node);
}

void Graph::Topological_Sort() {
    // DFS with one change (result.push_front())

    deque<int> result;
    vector<bool> visited(nodes);

    for (int i = 0; i != nodes; i++) {
        if (!visited[i]) {
            Topological_Sort_Algo(i, visited, result);
        }
    }

    // Print
    for (int i = 0; i != (int) result.size(); i++) {
        if (i != (int) result.size() - 1) {
            cout << result[i] << ", ";
        }
        else {
            cout << result[i] << endl;
        }
    }
}

int main() {

    int nodes, edges;
    cin >> nodes >> edges;
    Graph new_graph = Graph(nodes, edges);
    new_graph.Read_Graph();

    new_graph.Topological_Sort();

    return 0;
}
