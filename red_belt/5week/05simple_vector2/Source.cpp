#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <cstdint>
#include <memory>
#include <random>

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
#include <array>
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
#include <string_view>
#include <regex>
#include <iterator>
#include <numeric>

#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <functional>

#include "test_runner.h"
#include "profile.h"
#include "simple_vector.h"

void TestConstruction() {
	SimpleVector<int> empty;
	ASSERT_EQUAL(empty.Size(), 0u);
	ASSERT_EQUAL(empty.Capacity(), 0u);
	ASSERT(empty.begin() == empty.end());

	SimpleVector<std::string> five_strings(5);
	ASSERT_EQUAL(five_strings.Size(), 5u);
	ASSERT(five_strings.Size() <= five_strings.Capacity());
	for (auto& item : five_strings) {
		ASSERT(item.empty());
	}
	five_strings[2] = "Hello";
	ASSERT_EQUAL(five_strings[2], "Hello");
}

void TestPushBack() {
	SimpleVector<int> v;
	for (int i = 10; i >= 1; --i) {
		v.PushBack(i);
		ASSERT(v.Size() <= v.Capacity());
	}
	std::sort(std::begin(v), std::end(v));

	const std::vector<int> expected = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	ASSERT(std::equal(std::begin(v), std::end(v), std::begin(expected)));
}

class StringNonCopyable : public std::string {
public:
	using std::string::string;
	StringNonCopyable(std::string&& other) : std::string(move(other)) {}
	StringNonCopyable(const StringNonCopyable&) = delete;
	StringNonCopyable(StringNonCopyable&&) = default;
	StringNonCopyable& operator=(const StringNonCopyable&) = delete;
	StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
	SimpleVector<StringNonCopyable> strings;
	static const int SIZE = 10;
	for (int i = 0; i < SIZE; ++i) {
		strings.PushBack(StringNonCopyable(std::to_string(i)));
	}
	for (int i = 0; i < SIZE; ++i) {
		ASSERT_EQUAL(strings[i], std::to_string(i));
	}
}


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	TestRunner tr;
	RUN_TEST(tr, TestConstruction);
	RUN_TEST(tr, TestPushBack);
	RUN_TEST(tr, TestNoCopy);
	return 0;
}
