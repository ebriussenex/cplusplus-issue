#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

//#include <limits>
//
//#include <ios>
//#include <iosfwd>
#include <iostream>
//#include <sstream>
//#include <fstream>
//#include <cfenv>
//
//#include <stack>
//#include <queue>
//#include <deque>
//#include <vector>
//#include <set>
//#include <unordered_set>
//#include <map>
//#include <unordered_map>
//#include <utility>
//#include <list>
//#include <forward_list>
//#include <bitset>
//
//#include <iomanip>
//#include <algorithm>
//#include <string>
//#include <regex>
//#include <iterator>
//
//#include <cmath>
//#include <cstdio>
//#include <cctype>
//#include <cstring>
//#include <stdio.h>
//#include <stdlib.h>
//#include <chrono>
//#include <functional>

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


Rational operator+(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
}

bool operator==(const Rational& lhs, const Rational& rhs) {
	return (rhs.Numerator() == lhs.Numerator() && rhs.Denominator() == lhs.Denominator());
}


int main() {
	{
		Rational r1(4, 6);
		Rational r2(2, 3);
		bool equal = r1 == r2;
		if (!equal) {
			std::cout << "4/6 != 2/3" << std::endl;
			return 1;
		}
	}

	{
		Rational a(2, 3);
		Rational b(4, 3);
		Rational c = a + b;
		bool equal = c == Rational(2, 1);
		if (!equal) {
			std::cout << "2/3 + 4/3 != 2" << std::endl;
			return 2;
		}
	}

	{
		Rational a(5, 7);
		Rational b(2, 9);
		Rational c = a - b;
		bool equal = c == Rational(31, 63);
		if (!equal) {
			std::cout << "5/7 - 2/9 != 31/63" << std::endl;
			return 3;
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
