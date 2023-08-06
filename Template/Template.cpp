#include <bits/stdc++.h>

using namespace std;

#define FAST cin.tie(0)->sync_with_stdio(0)
#define mp make_pair
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

struct HASH {
    size_t operator()(const pair<int,int> &x) const {
        return hash<long long>()(((long long)x.first)^(((long long)x.second)<<32));
    }
};

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ii> vii;

const int MXN = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const ld EPS = 1e-9;

void solve() {
    int n; cin >> n;
    vi arr(n);
    for (auto &x : arr) { cin >> x; }
}

int main() {
    FAST;
    int TC = 1;
    // cin >> TC;
    for (int i = 1; i <= TC; i++) {
        // cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
