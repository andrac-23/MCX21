/*
 GCC compiler
 SOURCE:
  * https://www.youtube.com/watch?v=2FShdqn-Oz8
*/

#include <bits/stdc++.h>
using namespace std;

class Seg_Tree {
  public:
    Seg_Tree(int size, vector<int> &arr) {
      // Pad with 0's
      while (__builtin_popcount(size) != 1) {
        arr.push_back(0);
        size++;
      }
      this->size = size;

      tree.resize(2 * size);
      for (int i = 0; i < size; i++) {
        tree[size + i] = arr[i];
      }
      for (int i = size - 1; i >= 1; i--) {
        tree[i] = tree[2 * i] + tree[(2 * i) + 1];
      }
    }

    long long query(int idx_left, int idx_right) {
      if (idx_left == idx_right) {
        return tree[size + idx_left];
      }
      return query_Algo(1, 0, size - 1, idx_left, idx_right);
    }

    // Index must be [0...n-1]
    // TODO j updates range
    void update(int idx, int value, int j = 0) {
      tree[size + idx] = value;
      for (int i = (size + idx) / 2; i >= 1; i /= 2) {
        tree[i] = tree[2 * i] + tree[(2 * i) + 1];
      }
    }

  private:
    // Sum Query
    long long query_Algo(int node_idx, int node_left, int node_right, int idx_left, int idx_right) {
      // Interval contains query range
      if ((node_left >= idx_left) && (node_right <= idx_right)) {
        return tree[node_idx];
      }
      if ((node_left > idx_right) || (node_right < idx_left)) {
        // Disjoint interval
        return 0;
      }
      // Get children
      int half = (node_left + node_right) / 2;
      // [left, half] and [half + 1, right]
      long long sum = query_Algo(2 * node_idx, node_left, half, idx_left, idx_right) +
                      query_Algo(2 * node_idx + 1, half + 1, node_right, idx_left, idx_right);
      return sum;
    }

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

  Seg_Tree tree = Seg_Tree(size, array);

  while (TC--) {
    int operation;
    cin >> operation;
    if (operation == 1) { // update
      int index, new_value;
      cin >> index >> new_value;
      tree.update(index - 1, new_value);
    }
    else if (operation == 2) { // query
      int left_index, right_index;
      cin >> left_index >> right_index;
      cout << tree.query(left_index - 1, right_index - 1) << "\n";
    }
  }
  return 0;
}
