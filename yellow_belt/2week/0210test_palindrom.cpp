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

bool IsPalindrom(std::string word) {
	int n = word.length() - 1;
	for (int i = 0; i < n / 2 + 1; i++) {
		if (word[i] == word[n - i]);
		else return false;
	}
	return true;
}

void TestPalindrom() {
	AssertEqual(IsPalindrom(""), true, "Check void");
	AssertEqual(IsPalindrom("  "), true, "Check d-space");
	AssertEqual(IsPalindrom("aa"), true, "aa is palindrom");
	AssertEqual(IsPalindrom("a"), true, "a is palindrom");
	AssertEqual(IsPalindrom(" "), true, "Chack space");
	AssertEqual(IsPalindrom("madam"), true, "madam is palindrom");
	AssertEqual(IsPalindrom(" madam "), true, " madam  is palindrom");
	AssertEqual(IsPalindrom(" madam;"), false, " madam; is not palindrom");
	AssertEqual(IsPalindrom(" madam"), false, " madam is not palindrom");
	AssertEqual(IsPalindrom("abab"), false, "abab is not palindrom");
	AssertEqual(IsPalindrom("abacfdcaba"), false, "abacfdcaba is not palindrom");
	AssertEqual(IsPalindrom("ma d am"), true, "ma d am is palindrom");
	AssertEqual(IsPalindrom("ma:d:am"), true, "ma:d:am is palindrom");
	AssertEqual(IsPalindrom("aba cba"), false, "aba cba is not palindrom");
	AssertEqual(IsPalindrom("ma  am"), true, "ma  am is palindrom");
	AssertEqual(IsPalindrom("ma dam"), false, "ma dam is palindrom");

}
int main() {
	TestRunner runner;
	runner.RunTest(TestPalindrom, "Test palindrom");
	return 0;
}