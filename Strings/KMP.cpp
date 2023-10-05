/*

  SOURCE:

   * S. Halim e F. Halim. Competitive Programming 2, Second Edition Lulu

*/

#include <bits/stdc++.h>

using namespace std;

vector<int> createLPS(string& p, int m) {
    vector<int> LPS(m, 0);
    int i = 1, prevLPS = 0;
    while (i < m) {
        if (p[i] == p[prevLPS]) {
            LPS[i++] = ++prevLPS;
        }
        else if (prevLPS == 0) {
            LPS[i++] = 0;
        }
        else {
            prevLPS = LPS[prevLPS - 1];
        }
    }
    return LPS;
}

void KMP(string& st, string& p) {
    // Finds occurrences of pattern p in st
    int n = (int) st.size(), m = (int) p.size();
    vector<int> LPS = createLPS(p, m);
    int i = 0, j = 0;
    while (i < n) {
        if (st[i] == p[j]) {
            i++; j++;
        }
        else {
            j ? j = LPS[j - 1] : i++;
        }
        if (j == m) {
            cout << "Found pattern at index " << i - j << "\n";
            j = LPS[j - 1];
        }
    }
}

int main() {
    string st = "mississippi", p = "issip";
    KMP(st, p);
    return 0;
}
