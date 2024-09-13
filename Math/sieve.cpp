#include <bits/stdc++.h>

using namespace std;

class Sieve {
public:
    Sieve(int n) {
        this->is_prime.resize(n + 1, true);
        this->n = n;
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i <= n; i++) {
            if (is_prime[i]) {
                primes.push_back(i);
                for (long long j = (long long) i * i; j <= n; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }

    bool is_prime_number(long long n) {
        if (n <= this->n) {
            return is_prime[n];
        }
        for (int p : primes) {
            if (n % p == 0) {
                return false;
            }
            if ((long long) p * p > n) {
                break;
            }
        }
        return true;
    }

    vector<int> prime_factors(long long n) {
        vector<int> factors;
        for (int p : primes) {
            if (n % p == 0) {
                factors.push_back(p);
                while (n % p == 0) {
                    // factors.push_back(p); // if power is needed
                    n /= p;
                }
            }
            if ((long long) p * p > n) {
                break;
            }
        }
        if (n > 1) {
            factors.push_back(n);
        }
        return factors;
    }

vector<bool> is_prime;
vector<int> primes;
int n;
};

int main() {
    Sieve sieve(100000000);
    cout << sieve.is_prime_number(104729) << endl;
    return 0;
}
