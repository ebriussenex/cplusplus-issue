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
//#include "simple_vector.h"

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	size_t distance = range_end - range_begin;
	if (distance < 2) {
		return;
	}
	std::vector<typename RandomIt::value_type> target(std::make_move_iterator(range_begin), std::make_move_iterator(range_end));
	std::vector<typename RandomIt::value_type> temp;
	temp.reserve(distance);

	auto first_incision = target.begin() + distance / 3;
	auto second_incision = first_incision + distance / 3;

	MergeSort(target.begin(), first_incision);
	MergeSort(first_incision, second_incision);
	MergeSort(second_incision, target.end());
	std::merge(std::make_move_iterator(target.begin()), std::make_move_iterator(first_incision),
		std::make_move_iterator(first_incision), std::make_move_iterator(second_incision),
		std::back_inserter(temp));
	std::merge(std::make_move_iterator(temp.begin()), std::make_move_iterator(temp.end()),
		std::make_move_iterator(second_incision), std::make_move_iterator(target.end()),
		range_begin);
}

void TestIntVector() {
	std::vector<int> numbers = { 6, 1, 3, 9, 1, 9, 8, 12, 1 };
	MergeSort(begin(numbers), end(numbers));
	ASSERT(std::is_sorted(begin(numbers), end(numbers)));
}


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	TestRunner tr;
	RUN_TEST(tr, TestIntVector);
	return 0;
}
