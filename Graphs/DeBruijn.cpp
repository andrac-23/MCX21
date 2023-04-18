/*

  Constructs DeBruijn Graph
  and prints a DeBruijn sequence

  Also solution to https://leetcode.com/problems/cracking-the-safe/

*/

#include <bits/stdc++.h>

using namespace std;

unordered_map<string, int> positions;

void Generate_Subsets(int digits, int alphabet, string &aux, vector<string> &strings) {
    if (digits == 0) {
        return;
    }
    for (int i = 0; i != alphabet; i++) {
        aux.push_back(i + '0');
        Generate_Subsets(digits-1, alphabet, aux, strings);
        if (digits == 1) {
            strings.push_back(aux);
        }
        aux.pop_back();
    }
}

vector<pair<string, vector<string>>> Create_Graph(int digits, int alphabet) {
    // Create a Graph with all subsets of the set
    // {alphabet}^(digits-1) as nodes
    int nodes = pow(alphabet, digits-1);
    vector<pair<string, vector<string>>> adjacency_list;
    adjacency_list.resize(nodes);

    string aux = "";
    vector<string> strings;

    Generate_Subsets(digits-1, alphabet, aux, strings);

    // Assign each string to a node and create edges
    for (int i = 0; i != nodes; i++) {
        adjacency_list[i].first = strings[i];
        // Create edges
        string curr = ""; for (int s = 1; s < digits-1; s++) { curr+= strings[i][s];}
        for (int j = 0; j != alphabet; j++) {
            adjacency_list[i].second.push_back(curr + to_string(j));
        }
    }
    // Map each string with their position
    for (int i = 0; i != nodes; i ++) {
        positions[adjacency_list[i].first] = i;
    }
    return adjacency_list;
}

void Euler_Circuit(vector<pair<string, vector<string>>> &adjacency_list, int digits) {
    // Create the Eulerian Circuit
    stack<pair<int, char>> to_Visit;
    to_Visit.push({0, -1});
    string circuit;
    while(!to_Visit.empty()) {
        int curr_node = to_Visit.top().first;
        char curr_edge = to_Visit.top().second;
        if (!adjacency_list[curr_node].second.empty()) {
            // Choose edge
            string curr_string = adjacency_list[curr_node].second.back();
            int new_node = positions[curr_string];
            char new_edge = curr_string.back();

            to_Visit.push({new_node, new_edge});
            adjacency_list[curr_node].second.pop_back();
        }
        else {
            to_Visit.pop();
            if (curr_edge != -1) {
                circuit.push_back(curr_edge);
            }
        }
    }
    // Add digits-1 first digits and print the circuit
    for (int i = 0; i != digits - 1; i++) {
        circuit.push_back(circuit[i]);
    }
    // Print
    cout << circuit << endl;
}

int main() {
    int digits, alphabet;
    cin >> digits >> alphabet;
    if (digits == 1) {
        for (int i = 0; i != alphabet; i++) {
            cout << i;
        }
        cout << endl;
    }
    else {
        vector<pair<string, vector<string>>> adjacency_list = Create_Graph(digits, alphabet);
        Euler_Circuit(adjacency_list, digits);
    }
    return 0;
}
