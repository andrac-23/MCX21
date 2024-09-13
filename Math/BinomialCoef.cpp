#include <bits/stdc++.h>

using namespace std;

constexpr int MxN = 1e6;
constexpr int MOD = 1e9 + 7;

vector<long long> factorial(MxN + 1, 1);

long long inverse(long long a) {
    // Only for prime MOD
    if (a <= 1) {
        return a;
    }
    return MOD - (long long)(MOD/a) * inverse(MOD % a) % MOD;
}

long long binomial_coefficient(int n, int k) {
    return factorial[n] * inverse(factorial[k] * factorial[n - k] % MOD) % MOD;
}

int main() {
    for (int i = 1; i <= MxN; i++) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
    cout << binomial_coefficient(5, 2) << endl;
}
