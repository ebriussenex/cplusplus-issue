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
std::ostream & operator << (std::ostream & os, const std::vector<T> & s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
std::ostream& operator << (std::ostream& os, const std::map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
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
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
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

int GetDistinctRealRootCount(double a, double b, double c) {
	if (a) {
		double d = b * b - 4 * a * c;
		if (d > 0)	return 2;
		else if (d == 0)	return 1;
		else    return 0;
	}
	else if (b)
		return 1;
	else if (c)
		return 0;
}

void Adequate() {
	int count;
	count = GetDistinctRealRootCount(1, 0, 1);
	Assert(count >= 0 && count <= 2, "More than 2 or less than 0 roots");
	count = GetDistinctRealRootCount(1, 1, 1);
	Assert(count >= 0 && count <= 2, "More than 2 or less than 0 roots");
	count = GetDistinctRealRootCount(-10, 10, -10);
	Assert(count >= 0 && count <= 2, "More than 2 or less than 0 roots");
	count = GetDistinctRealRootCount(10, 10, 10);
	Assert(count >= 0 && count <= 2, "More than 2 or less than 0 roots");
	count = GetDistinctRealRootCount(-1, 0, -1);
	Assert(count >= 0 && count <= 2, "More than 2 or less than 0 roots");
	count = GetDistinctRealRootCount(1, -2, 1);
	Assert(count >= 0 && count <= 2, "More than 2 or less than 0 roots");
	count = GetDistinctRealRootCount(-1, 0, 0);
	Assert(count >= 0 && count <= 2, "More than 2 or less than 0 roots");
	count = GetDistinctRealRootCount(1, 0, 0);
	Assert(count >= 0 && count <= 2, "More than 2 or less than 0 roots");
	count = GetDistinctRealRootCount(-1, 0, 1);
	Assert(count >= 0 && count <= 2, "More than 2 or less than 0 roots");
	count = GetDistinctRealRootCount(0, 1, 1);
	Assert(count >= 0 && count <= 2, "More than 2 or less than 0 roots");
	count = GetDistinctRealRootCount(0, -1, 0);
	Assert(count >= 0 && count <= 2, "More than 2 or less than 0 roots");
	count = GetDistinctRealRootCount(0, 1, 0);
	Assert(count >= 0 && count <= 2, "More than 2 or less than 0 roots");
	count = GetDistinctRealRootCount(0, 0, 1);
	Assert(count >= 0 && count <= 2, "More than 2 or less than 0 roots");
	count = GetDistinctRealRootCount(0, 0, -1);
	Assert(count >= 0 && count <= 2, "More than 2 or less than 0 roots");
}

void TestTwoRoots() {
	AssertEqual(GetDistinctRealRootCount(-1, 0, 1), 2, "-x^2 + 1 has 2 real roots");
	AssertEqual(GetDistinctRealRootCount(1, 3, -4), 2, "x^2 + 3*x - 4 has 2 real roots");
}

void TestNoRoot() {
	AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0, "x^2 + 1 has no real root");
	AssertEqual(GetDistinctRealRootCount(1, 1, 1), 0, "x^2 + x + 1 has no real root");
	AssertEqual(GetDistinctRealRootCount(-10, 10, -10), 0, "-10*x^2 + 10*x - 10 has no real root");
	AssertEqual(GetDistinctRealRootCount(10, 10, 10), 0, "10*x^2 + 10*x + 10 has no real root");
	AssertEqual(GetDistinctRealRootCount(-1, 0, -1), 0, "-x^2-1 has no real root");
}

void TestOneRoot() {
	AssertEqual(GetDistinctRealRootCount(1, -2, 1), 1, "x^2 - 2x + 1 has 1 real root");
	AssertEqual(GetDistinctRealRootCount(1, 2, 1), 1, "x^2 + 2x + 1 has 1 real root");
	AssertEqual(GetDistinctRealRootCount(-1, 0, 0), 1, "-x^2 = 0 has 1 real root");
	AssertEqual(GetDistinctRealRootCount(1, 0, 0), 1, "x^2 = 0 has 1 real root");
}

void TestLinearEquation() {
	AssertEqual(GetDistinctRealRootCount(0, 1, 1), 1, "x + 1 has 1 real root");
	AssertEqual(GetDistinctRealRootCount(0, -1, 0), 1, "-x has 1 real root");
	AssertEqual(GetDistinctRealRootCount(0, 1, 0), 1, "x has 1 real root");
	AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "1 = 0, x has no real root");
	AssertEqual(GetDistinctRealRootCount(0, 0, -1), 0, "-1 = 0, x has no real root");
}

int main() {
	TestRunner runner;
	runner.RunTest(TestLinearEquation, "TestLinearEquation");
	runner.RunTest(TestOneRoot, "TestOneRoot");
	runner.RunTest(TestNoRoot, "TestNoRoot");
	runner.RunTest(Adequate, "Adequate");
	runner.RunTest(TestTwoRoots, "TestTwoRoots");
	return 0;
}
