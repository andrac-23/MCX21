/*

  SOURCE:

   * SLIDES AULA 3 - Estruturas de Dados Avancadas
   * S. Halim e F. Halim. Competitive Programming 2, Second Edition Lulu

*/

#include <bits/stdc++.h>

using namespace std;

class DS_Union {
    public:
        DS_Union(int numSets) {
            this->numSets = numSets;
            setSize.assign(numSets, 1);
            rank.assign(numSets, 0);
            parents.assign(numSets, 0);

            // We start with n sets of size 1
            for (int i = 0; i < numSets; i++) {
                parents[i] = i;
            }
        }

        // returns parent
        int find_set(int node) {
            if (parents[node] == node) {
                return node;
            }
            parents[node] = find_set(parents[node]);
            return parents[node];
        }

        bool is_same_set(int node_a, int node_b) {
            return (find_set(node_a) == find_set(node_b));
        }

        void set_union(int node_a, int node_b) {
            if (!is_same_set(node_a, node_b)) {
                numSets--;
            }

            int pa = find_set(node_a);
            int pb = find_set(node_b);

            if (rank[pa] > rank[pb]) {
                parents[pb] = pa;
                setSize[pa] += setSize[pb];
            }

            else {
                parents[pa] = pb;
                setSize[pb] += setSize[pa];
                if (rank[pa] == rank[pb]) {
                    rank[pb]++;
                }
            }
        }

        int numDisjointSets() {
            return numSets;
        }

        int sizeOfSet(int node) {
            return setSize[find_set(node)];
        }

    private:
        vector<int> parents, rank, setSize;
        int numSets;
};

int main() {



    return 0;
}
