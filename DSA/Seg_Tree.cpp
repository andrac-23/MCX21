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

    long long Query(int index_left, int index_right) {
      if (index_left == index_right) {
        return tree[size + index_left];
      }
      return Query_Algo(1, 0, size - 1, index_left, index_right);
    }

    // Index must be [0...n-1]
    // TODO j updates range
    void Update(int index, int value, int j = 0) {
      tree[size + index] = value;
      for (int i = (size + index)/2; i >= 1; i = i/2) {
        tree[i] = tree[2 * i] + tree[(2 * i) + 1];
      }
    }

  private:

    vector<long long> tree;
    int size;

    // Sum Query
    long long Query_Algo(int node_index, int node_left, int node_right, int index_left, int index_right) {
      if ((node_left >= index_left) && (node_right <= index_right)) {
        return tree[node_index];
      }
      if ((node_left > index_right) || (node_right < index_left)) {
        // Should not contribute to the answer, return identity element.
        return 0;
      }

      int new_bound = (node_left + node_right) / 2;

      long long sum = Query_Algo(node_index * 2, node_left, new_bound, index_left, index_right) // left child
              + Query_Algo((node_index * 2) + 1, new_bound + 1, node_right, index_left, index_right); // right child
      return sum;
    }

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
      tree.Update(index - 1, new_value);
    }
    else if (operation == 2) { // query
      int left_index, right_index;
      cin >> left_index >> right_index;
      cout << tree.Query(left_index - 1, right_index - 1) << "\n";
    }
  }
  return 0;
}
