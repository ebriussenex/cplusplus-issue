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

using namespace std;




template <typename String>
using Group = vector<String>;


template <typename String>
using Char = typename String::value_type;

template <typename String>
String RemoveNonUnique(const String& str_s) {
	auto str = str_s;
	sort(str.begin(), str.end());
	auto last = unique(str.begin(), str.end());
	str.erase(last, str.end());
	return str;
}

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
	map <String, Group<String>> groups_dict;
	vector <Group<String>> groups;
	for (String& item : strings) {
		groups_dict[RemoveNonUnique(item)].push_back(move(item));
	}
	for (auto& item : groups_dict) {
		groups.push_back(move(item.second));
	}
	return groups;
}


void TestGroupingABC() {
	vector<string> strings = { "caab", "abc", "cccc", "bacc", "c" };
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 2);
	sort(begin(groups), end(groups));
	ASSERT_EQUAL(groups[0], vector<string>({ "caab", "abc", "bacc" }));
	ASSERT_EQUAL(groups[1], vector<string>({ "cccc", "c" }));
}

void TestGroupingReal() {
	vector<string> strings = { "law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl" };
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 4);
	sort(begin(groups), end(groups));
	ASSERT_EQUAL(groups[0], vector<string>({ "laptop", "paloalto" }));
	ASSERT_EQUAL(groups[1], vector<string>({ "law", "wall", "awl" }));
	ASSERT_EQUAL(groups[2], vector<string>({ "port" }));
	ASSERT_EQUAL(groups[3], vector<string>({ "top", "pot" }));
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	TestRunner tr;
	RUN_TEST(tr, TestGroupingABC);
	RUN_TEST(tr, TestGroupingReal);
	return 0;
}
