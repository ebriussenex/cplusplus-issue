#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>
#include <exception>

#include <ios>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cfenv>
#include <iomanip>

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
		if (denominator == 0)	throw std::invalid_argument("invalid_argument");
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
	double Value() const {
		return numerator_ / denominator_;
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

Rational operator*(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
	if (rhs.Numerator() == 0) throw std::domain_error("domain_error");
	return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
}

std::istream& operator>>(std::istream& stream, Rational& rational) {
	int num, denum;
	if (stream >> num && stream.ignore(1) && stream >> denum) {
		rational = Rational(num, denum);
	}
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Rational& rational) {
	stream << rational.Numerator() << '/' << rational.Denominator();
	return stream;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
	return(lhs.Numerator() * rhs.Denominator() < lhs.Denominator() * rhs.Numerator());
}

int main() {
	try {
		Rational r(1, 0);
		std::cout << "Doesn't throw in case of zero denominator" << std::endl;
		return 1;
	}
	catch (std::invalid_argument&) {
	}

	try {
		auto x = Rational(1, 2) / Rational(0, 1);
		std::cout << "Doesn't throw in case of division by zero" << std::endl;
		return 2;
	}
	catch (std::domain_error&) {
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
