/*

  SOURCE:

   * S. Halim e F. Halim. Competitive Programming 2, Second Edition Lulu

*/

#include <bits/stdc++.h>

using namespace std;

class DSU {
public:
    DSU(int n) {
        // Init with n nodes (0-indexed)
        this->ranks.resize(n, 0);
        this->numSets = 0;
        for (int i = 0; i < n; i++) {
            parents.push_back(i);
        }
    }
    int Find_Parent(int a) {
        // Path compression
        if (parents[a] == a) {
            return a;
        }
        return parents[a] = Find_Parent(parents[a]);
    }
    bool Same_Set(int a, int b) {
        return (Find_Parent(a) == Find_Parent(b));
    }
    void Union(int a, int b) {
        int pa = Find_Parent(a);
        int pb = Find_Parent(b);
        if (pa == pb) return;
        numSets--;
        // Union by rank
        if (ranks[pa] > ranks[pb]) {
            parents[pb] = pa;
        }
        else {
            if (ranks[pa] == ranks[pb]) {
                ranks[pb]++;
            }
            parents[pa] = pb;
        }
    }
    int numSets;
private:
    vector<int> parents;
    vector<int> ranks;
    // vector<int> setSize;
};
