#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <cstdint>

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
#include <tuple>
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

template <class T>
std::ostream & operator<< (std::ostream & os, const std::vector<T> & s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) os << ", ";
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
std::ostream& operator<< (std::ostream& os, const std::set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) os << ", ";
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
std::ostream& operator<< (std::ostream& os, const std::map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) os << ", ";
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint = {}) {
	if (t != u) {
		std::ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) os << " hint: " << hint;
		throw std::runtime_error(os.str());
	}
}

void Assert(bool b, const std::string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const std::string& test_name) {
		try {
			func();
			std::cerr << test_name << " OK" << std::endl;
		}
		catch (std::exception& e) {
			++fail_count;
			std::cerr << test_name << " fail: " << e.what() << std::endl;
		}
		catch (...) {
			++fail_count;
			std::cerr << "Unknown exception caught" << std::endl;
		}
	}
	~TestRunner() {
		if (fail_count > 0) {
			std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
			exit(1);
		}
	}
private:
	int fail_count = 0;
};

int gcd(int a, int b);

class Rational {
public:
	Rational() {
		numerator_ = 0;
		denominator_ = 1;
	}
	Rational(int numerator, int denominator) {
		if (denominator == 0)	throw std::invalid_argument("Invalid argument");
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

void TestConstructor() {
	Rational number;
	AssertEqual(number.Numerator(), 0, "Constructor creates 0/1, your numerator is wrong");
	AssertEqual(number.Denominator(), 1, "Constructor creates 0/1, your denominator is wrong");
}

void TestLogic() {
	Rational number(4, 6);
	AssertEqual(number.Numerator(), 2, "4/6 -> 2/3, numerator is wrong");
	AssertEqual(number.Denominator(), 3, "4/6 -> 2/3, denominator is wrong");
	number = { 2, -3 };
	AssertEqual(number.Numerator(), -2, "2/(-3) == (-2)/3, numerator is wrong");
	AssertEqual(number.Denominator(), 3, "2/(-3) == (-2)/3, denominator is wrong");
	number = { -2, 3 };
	AssertEqual(number.Numerator(), -2, "(-2)/3 == (-2)/3, numerator is wrong");
	AssertEqual(number.Denominator(), 3, "(-2)/3 == (-2)/3, denominator is wrong");
	number = { -2, -3 };
	AssertEqual(number.Numerator(), 2, "-2/(-3) -> 2/3, numerator is wrong");
	AssertEqual(number.Denominator(), 3, "-2/(-3) -> 2/3, denominator is wrong");
	number = { 2, 3 };
	AssertEqual(number.Numerator(), 2, "2/3 -> 2/3 numerator is wrong");
	AssertEqual(number.Denominator(), 3, "2/3 -> 2/3, denominator is wrong");
	number = { 1, 1 };
	AssertEqual(number.Numerator(), 1, "1/1 -> 1/1 something wrong with numerator");
	AssertEqual(number.Denominator(), 1, "1/1 -> 1/1 something wrong with denominator");
	number = { 3, 3 };
	AssertEqual(number.Numerator(), 1, "3/3 -> 1/1 something wrong with numerator");
	AssertEqual(number.Denominator(), 1, "3/3 -> 1/1 something wrong with denominator");
	number = { 222, 222 };
	AssertEqual(number.Numerator(), 1, "222/222 -> 1/1 something wrong with numerator");
	AssertEqual(number.Denominator(), 1, "222/222 -> 1/1 something wrong with denominator");
	number = { 0 , 14 };
	AssertEqual(number.Numerator(), 0, "0/14 -> 0/1 something wrong with numerator");
	AssertEqual(number.Denominator(), 1, "0/14 -> 0/1 something wrong with denominator");

	number = { 4, -6 };
	AssertEqual(number.Numerator(), -2, "4/(-6) == (-2)/3, numerator is wrong");
	AssertEqual(number.Denominator(), 3, "4/(-6) == (-2)/3, denominator is wrong");
	number = { -4, 6 };
	AssertEqual(number.Numerator(), -2, "(-4)/6 == (-2)/3, numerator is wrong");
	AssertEqual(number.Denominator(), 3, "(-4)/6 == (-2)/3, denominator is wrong");
	number = { -4, -6 };
	AssertEqual(number.Numerator(), 2, "-4/(-6) -> 2/3, numerator is wrong");
	AssertEqual(number.Denominator(), 3, "-4/(-6) -> 2/3, denominator is wrong");

	number = { 27, 6 };
	AssertEqual(number.Numerator(), 9, "27/6 == 9/2, numerator is wrong");
	AssertEqual(number.Denominator(), 2, "27/6 == 9/2, denominator is wrong");
	number = { 27, -6 };
	AssertEqual(number.Numerator(), -9, "27/-6 == -9/2, numerator is wrong");
	AssertEqual(number.Denominator(), 2, "27/-6 == -9/2, denominator is wrong");
	number = { -27, 6 };
	AssertEqual(number.Numerator(), -9, "-27/6 == -9/2, numerator is wrong");
	AssertEqual(number.Denominator(), 2, "-27/6 == -9/2, denominator is wrong");
	number = { -27, -6 };
	AssertEqual(number.Numerator(), 9, "-27/-6 == 9/2, numerator is wrong");
	AssertEqual(number.Denominator(), 2, "-27/-6 == 9/2, denominator is wrong");

	number = { 147, 126 };
	AssertEqual(number.Numerator(), 7, "147/126 == 7/6, numerator is wrong");
	AssertEqual(number.Denominator(), 6, "147/126 == 7/6, denominator is wrong");
	number = { 147, -126 };
	AssertEqual(number.Numerator(), -7, "147/-126 == -7/6, numerator is wrong");
	AssertEqual(number.Denominator(), 6, "147/-126 == -7/6, denominator is wrong");
	number = { -147, 126 };
	AssertEqual(number.Numerator(), -7, "-147/126 == -7/6, numerator is wrong");
	AssertEqual(number.Denominator(), 6, "-147/126 == -7/6, denominator is wrong");
	number = { -147, -126 };
	AssertEqual(number.Numerator(), 7, "-147/-126 == 7/6, numerator is wrong");
	AssertEqual(number.Denominator(), 6, "-147/-126 == 7/6, denominator is wrong");
}

int main() {
	TestRunner runner;
	runner.RunTest(TestLogic, "Logic test");
	runner.RunTest(TestConstructor, "Constructor test");
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
