#include <bits/stdc++.h>

using namespace std;

// Source: Halim Halim
long long gcdEuclid(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return gcdEuclid(b, a % b);
}

long long extendedEuclid(long long a, long long b, long long& x, long long& y) {
    // Bézout coefficients
    // ax + by = gcd(a, b) (d)
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long d = extendedEuclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

long long lcm(long long a, long long b) {
    return a * (b / gcdEuclid(a, b));
}
