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
std::ostream& operator<< (std::ostream& os, const std::vector<T>& s) {
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

std::string FindNameByYear(const std::map<int, std::string>& names, int year) {
	std::string name;
	for (const auto& item : names) {
		if (item.first <= year)	name = item.second;
		else break;
	}
	return name;
}

class Person {
public:
	void ChangeFirstName(int year, const std::string& first_name) {
		first_names[year] = first_name;
	}
	void ChangeLastName(int year, const std::string& last_name) {
		last_names[year] = last_name;
	}
	std::string GetFullName(int year) {
		const std::string first_name = FindNameByYear(first_names, year);
		const std::string last_name = FindNameByYear(last_names, year);
		if (first_name.empty() && last_name.empty()) return "Incognito";
		else if (first_name.empty()) return last_name + " with unknown first name";
		else if (last_name.empty())	return first_name + " with unknown last name";
		else	return first_name + " " + last_name;
	}
private:
	std::map<int, std::string> first_names;
	std::map<int, std::string> last_names;
};

void TestLogic() {
	Person person;
	AssertEqual(person.GetFullName(1), "Incognito", "Correct output: Incognito");
	person.ChangeFirstName(2, "a");
	AssertEqual(person.GetFullName(2), "a with unknown last name", "Correct output: a with unknown last name");
	AssertEqual(person.GetFullName(1), "Incognito", "Correct output: Incognito");
	AssertEqual(person.GetFullName(153), "a with unknown last name", "Correct output: a with unknown last name");
	person.ChangeLastName(3, "b");
	AssertEqual(person.GetFullName(2), "a with unknown last name", "Correct output: a with unknown last name");
	AssertEqual(person.GetFullName(1), "Incognito", "Correct output: Incognito");
	AssertEqual(person.GetFullName(3), "a b", "Correct output: a b");
	AssertEqual(person.GetFullName(153), "a b", "Correct output: a b");
	person.ChangeLastName(1, "c");
	AssertEqual(person.GetFullName(0), "Incognito", "Correct output: Incognito");
	AssertEqual(person.GetFullName(2), "a c", "Correct output: a c");
	AssertEqual(person.GetFullName(3), "a b", "Correct output: a b");
	AssertEqual(person.GetFullName(1), "c with unknown first name", "Correct output: c with unknown first name");
	AssertEqual(person.GetFullName(155), "a b", "Correct output: a b");
	person.ChangeLastName(-2, "b");
	AssertEqual(person.GetFullName(-1), "b with unknown first name", "Correct output: b with unknown first name");
	AssertEqual(person.GetFullName(-2), "b with unknown first name", "Correct output: b with unknown first name");
	AssertEqual(person.GetFullName(2), "a c", "Correct output: a c");
	person.ChangeFirstName(-4, "ash");
	AssertEqual(person.GetFullName(-3), "ash with unknown last name", "Correct output: ash with unknown last name");
	AssertEqual(person.GetFullName(-2), "ash b", "Correct output: ash b");
	AssertEqual(person.GetFullName(153), "a b", "Correct output: a b");
}

int main() {
	TestRunner runner;
	Person person;
	runner.RunTest(TestLogic, "Logic test");
	return 0;
}
