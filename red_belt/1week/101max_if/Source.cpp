#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <cstdint>
#include <memory>

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

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
	ForwardIterator curr =  std::find_if(first, last, pred);
	for (auto it = first; it != last; it++) {
		if (pred(*it) && *it > *curr){
			curr = it;
		}
	}
	return curr;
}

void TestUniqueMax() {
	auto IsEven = [](int x) {
		return x % 2 == 0;
	};
	const std::list<int> hill{ 2, 4, 8, 9, 6, 4, 2 };
	auto max_iterator = hill.begin();
	advance(max_iterator, 2);
	std::vector<int> numbers(10);
	std::iota(numbers.begin(), numbers.end(), 1);
	Assert(
		max_element_if(numbers.begin(), numbers.end(), IsEven) == --numbers.end(),
		"Expect the last element"
	);
	Assert(
		max_element_if(hill.begin(), hill.end(), IsEven) == max_iterator,
		"Expect the maximal even number"
	);
}

void TestSeveralMax() {
	struct IsCapitalized {
		bool operator()(const std::string& s) {
			return !s.empty() && isupper(s.front());
		}
	};

	const std::forward_list<std::string> text{ "One", "two", "Three", "One", "Two",
	  "Three", "one", "Two", "three" };
	auto max_iterator = text.begin();
	advance(max_iterator, 4);

	Assert(
		max_element_if(text.begin(), text.end(), IsCapitalized()) == max_iterator,
		"Expect thr first \"Two\""
	);
}

void TestNoMax() {
	const std::vector<int> empty;
	const std::string str = "Non-empty string";

	auto AlwaysTrue = [](int) {
		return true;
	};
	Assert(
		max_element_if(empty.begin(), empty.end(), AlwaysTrue) == empty.end(),
		"Expect end for empty container"
	);

	auto AlwaysFalse = [](char) {
		return false;
	};
	Assert(
		max_element_if(str.begin(), str.end(), AlwaysFalse) == str.end(),
		"Expect end for AlwaysFalse predicate"
	);
}

int main() {
	TestRunner tr;
	tr.RunTest(TestUniqueMax, "TestUniqueMax");
	tr.RunTest(TestSeveralMax, "TestSeveralMax");
	tr.RunTest(TestNoMax, "TestNoMax");
	return 0;
}