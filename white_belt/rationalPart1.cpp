#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>

#include <ios>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cfenv>

#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <utility>
#include <list>
#include <forward_list>
#include <bitset>

#include <iomanip>
#include <algorithm>
#include <string>
#include <regex>
#include <iterator>

#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

#include <chrono>
#include <functional>

int gcd(int a, int b);

class Rational {
public:
	Rational() {
		numerator_ = 0;
		denominator_ = 1;
	}
	Rational(int numerator, int denominator) {
		if (denominator < 0) {
			numerator = -numerator;
			denominator = -denominator;
		}
		int c = gcd(numerator, denominator);
		numerator /= c;
		denominator /= c;
		numerator_ = numerator;
		denominator_ = denominator;
	}
	int Numerator() const {
		return numerator_;
	}
	int Denominator() const {
		return denominator_;
	}
private:
	int numerator_;
	int denominator_;
};
int main() {
		{
			const Rational r(3, 10);
			if (r.Numerator() != 3 || r.Denominator() != 10) {
				std::cout << "Rational(3, 10) != 3/10" << std::endl;
				return 1;
			}
		}

		{
			const Rational r(8, 12);
			if (r.Numerator() != 2 || r.Denominator() != 3) {
				std::cout << "Rational(8, 12) != 2/3" << std::endl;
				return 2;
			}
		}

		{
			const Rational r(-4, 6);
			if (r.Numerator() != -2 || r.Denominator() != 3) {
				std::cout << "Rational(-4, 6) != -2/3" << std::endl;
				return 3;
			}
		}

		{
			const Rational r(4, -6);
			if (r.Numerator() != -2 || r.Denominator() != 3) {
				std::cout << "Rational(4, -6) != -2/3" << std::endl;
				return 3;
			}
		}

		{
			const Rational r(0, 15);
			if (r.Numerator() != 0 || r.Denominator() != 1) {
				std::cout << "Rational(0, 15) != 0/1" << std::endl;
				return 4;
			}
		}

		{
			const Rational defaultConstructed;
			if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
				std::cout << "Rational() != 0/1" << std::endl;
				return 5;
			}
		}

		std::cout << "OK" << std::endl;
	return 0;
}

int gcd(int a, int b) {
	int c;
	while (b) {
		c = a % b;
		a = b;
		b = c;
	}
	return abs(a);
}
