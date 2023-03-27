/*

SOURCES:

 * https://cp-algorithms.com/data_structures/fenwick.html

 * hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/tutorial/

*/

#include <bits/stdc++.h>

using namespace std;

// One Based Index
class Fenwick_Tree {
    public:
        Fenwick_Tree(int size, vector<int> &array) {
            this->size = size;

            tree.resize(this->size + 1);

            // Create Array
            for (int i = 1; i <= size; i++) {
                Update_Delta(i, array[i-1]);
            }
        }

        long long Sum_Query(int index_left, int index_right) {
            return Prefix_Sum(index_right) - Prefix_Sum(index_left - 1);
        }

        long long Prefix_Sum(int index) {
            long long sum = 0; // Identity element
            while (index > 0) {
                sum += tree[index];
                index -= (index) & (-index);
            }
            return sum;
        }

        void Update_Delta(int index, int value) {
            while (index <= size) {
                tree[index] += value;
                index += (index) & (-index);
            }
        }

    private:
        vector<long long> tree;
        int size;
};

int main() {

    int size, TC;
    cin >> size >> TC;

    vector<int> array(size);

    for (int i = 0; i < size; i++) {
        cin >> array[i];
    }

    Fenwick_Tree tree = Fenwick_Tree(size, array);

    while(TC--) {
        int operation;
        cin >> operation;
        if (operation == 1) {
            // update
            int index, value;
            cin >> index >> value;
            int delta = value - array[index - 1];
            array[index - 1] = value;
            tree.Update_Delta(index, delta);
        }
        if (operation == 2) {
            // query
            int index_left, index_right;
            cin >> index_left >> index_right;
            cout << tree.Sum_Query(index_left, index_right) << "\n";
        }
    }

    return 0;
}
