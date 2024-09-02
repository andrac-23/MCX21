#include <bits/stdc++.h>

using namespace std;

/*
**                  BigInt
**
** Normal operations with big integers.
**
** Sources: - Slides da Aula (Halim Halim 2nd ed)
**          - https://codeforces.com/blog/entry/1482
**
*/

class BigInt {
public:
	BigInt() : sign(1) { }

	BigInt(long long v) {
		*this = v;
	}

	BigInt(const string& s) {
		convert_s(s);
	}

	void operator=(const BigInt& v) {
		this->sign = v.sign;
		this->a = v.a;
	}

	void operator=(long long v) {
		this->sign = 1;
		if (v < 0) {
			this-> sign = -1;
			v = -v;
		}
		else if (v == 0) {
			this->a.push_back(0);
		}
		while (v > 0) {
			this->a.push_back(v % 10);
			v /= 10;
		}
	}

	BigInt operator+(const BigInt& v) const {
		if (this->sign == v.sign) {
			BigInt ans = v; // ans == v
			int carry = 0;
			for (int i = 0; i < max(this->a.size(), ans.a.size()) || carry; i++) {
				if (i == (int) ans.a.size()) {
					ans.a.push_back(0);
				}
				ans.a[i] += carry;
				if (i < (int) this->a.size()) {
					ans.a[i] += this->a[i];
				}
				if (ans.a[i] >= 10) {
					ans.a[i] -= 10;
					carry = 1;
				}
				else {
					carry = 0;
				}
			}
			ans.remove_trailing_zeroes();
			return ans;
		}
		// Negative
		return *this - (-v);
	}

	void operator+=(const BigInt& v) {
		*this = *this + v;
	}

	bool operator>(const BigInt& v) const {
		if (this->sign > v.sign) {
			return true;
		}
		if (this->a.size() > v.a.size()) {
			return true;
		}
		else if (this->a.size() == v.a.size()) {
			for (int i = (int) this->a.size() - 1; i >= 0; i--) {
				if (this->a[i] < v.a[i]) {
					return false;
				}
				else if (this->a[i] > v.a[i]) {
					return true;
				}
			}
		}
		return false;
	}

	bool operator<(const BigInt& v) const {
		return v > *this;
	}

	bool operator==(const BigInt& v) const {
		return !(*this > v) && !(*this < v);
	}

	bool operator!=(const BigInt& v) const {
		return !(*this == v);
	}

	bool operator>=(const BigInt& v) const {
		return (*this > v) || (*this == v);
	}

	bool operator<=(const BigInt& v) const {
		return (*this < v) || (*this == v);
	}

	BigInt operator-() const {
		BigInt ans = *this;
		ans.sign *= -1;
		return ans;
	}

	BigInt operator-(const BigInt& v) const {
		if (this->sign == v.sign) {
			if (this->absolute_value() >= v.absolute_value()) {
				BigInt ans = *this;
				int carry = 0;
				for (int i = 0; i < (int) this->a.size(); i++) {
					ans.a[i] -= carry;
					if (i < (int) v.a.size()) {
						ans.a[i] -= v.a[i];
					}
					if (ans.a[i] < 0) {
						ans.a[i] += 10;
						carry = 1;
					}
					else {
						carry = 0;
					}
				}
				ans.remove_trailing_zeroes();
				return ans;
			}
			return -(v - *this);
		}
		return *this + (-v);
	}

	void operator-=(const BigInt& v) {
		*this = *this - v;
	}

	BigInt operator*(const BigInt& v) const {
		BigInt ans = BigInt(0), tmp = *this;
		ans.sign = this->sign * v.sign;
		for (int i = 0; i < (int) v.a.size(); i++) {
			for (int j = 0; j < v.a[i]; j++) {
				ans += tmp;
			}
			tmp.digit_shift(0);
		}
		ans.remove_trailing_zeroes();
		return ans;
	}

	void operator*=(const BigInt& v) {
		*this = *this * v;
	}

	void digit_shift(short digit) {
		this->a.push_front(digit);
	}

	BigInt operator/(const BigInt& v) const {
		BigInt ans = 0, tmp = 0;
		ans.sign = this->sign * v.sign;
		for (int i = (int) this->a.size() - 1; i >= 0; i--) {
			tmp.digit_shift(this->a[i]);
			ans.digit_shift(0);
			tmp.remove_trailing_zeroes();
			while (tmp >= v) {
				ans.a[0]++;
				tmp -= v;
			}
		}
		ans.remove_trailing_zeroes();
		return ans;
	}

	void operator/=(const BigInt& v) {
		*this = *this / v;
	}

	BigInt operator%(const BigInt& v) const {
		BigInt ans = 0;
		for (int i = (int) this->a.size() - 1; i >= 0; i--) {
			ans.digit_shift(this->a[i]);
			ans.remove_trailing_zeroes();
			while (ans >= v) {
				ans -= v;
			}
		}
		return ans;
	}

	void operator%=(const BigInt& v) {
		*this = *this % v;
	}

	void remove_trailing_zeroes() {
		int total_removed = 0;
		for (int i = (int) this->a.size() - 1; i >= 0; i--) {
			if (this->a[i] != 0) {
				break;
			}
			total_removed++;
		}
		while (total_removed--) {
			this->a.pop_back();
		}
		if (this->a.size() == 0) {
			this->sign = 1;
			this->a.push_back(0);
		}
	}

	BigInt absolute_value() const {
		BigInt ans = *this;
		ans.sign = 1;
		return ans;
	}

	friend ostream& operator<<(std::ostream& os, const BigInt& obj);
private:
	deque<int> a;
	int sign;

	void convert_s(const string& s) {
		this->sign = (s[0] == '-' ? -1 : 1);
		this->a.clear();
		for (int i = (int) s.size() - 1; i >= 0; i--) {
			if (s[i] == '-') break;
			int curr_digit = s[i] - '0';
			a.push_back(curr_digit);
		}
		this->remove_trailing_zeroes();
	}
};

ostream& operator<<(std::ostream& os, const BigInt& a) {
	if (a.sign == -1) {
		os << "-";
	}
	if (a.a.empty()) { os << "0"; }
	for (int i = (int) a.a.size() - 1; i >= 0; i--) {
		os << a.a[i];
	}
	return os;
}

/*
 * Returns a^b.
*/
BigInt pow(const BigInt& a, const BigInt& b) {
	BigInt ans = 1, base = a, exp = b;
	BigInt zero = 0, two = 2;
	while (exp > zero) {
		if (exp % two != zero) {
			ans *= base;
		}
		base *= base;
		exp /= two;
	}
	return ans;
}

/*
int main() {
    BigInt a = BigInt(5);
    BigInt b = BigInt("99999999999999999999");
    cout << (a < b) << endl;
    cout << a + b << endl;
    cout << a - b << endl;
    cout << a * b << endl;
    cout << b / a << endl;
}
*/
