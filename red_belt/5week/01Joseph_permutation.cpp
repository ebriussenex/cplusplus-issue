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


template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, const uint32_t step_size) {
	std::list<typename RandomIt::value_type> lpool;
	for (auto pos = first; pos != last; pos++) {
		lpool.push_back(std::move(*pos));
	}
	auto pos = lpool.begin();
	while (!lpool.empty()) {
		*(first++) = std::move(*pos);
		if (lpool.size() == 1) {
			break;
		}
		auto next_pos = lpool.begin();
		if (std::next(pos) != lpool.end()) {
			next_pos = std::next(pos);
		}
		lpool.erase(pos);
		pos = next_pos;
		for (size_t i = 0; i < step_size - 1; i++) {
			if (std::next(pos) == lpool.end()) {
				pos = lpool.begin();
			}
			else pos = std::next(pos);
		}
	}
}

//creates a "1, 2, 3, ... 10" vector
std::vector<int> MakeTestVector() {
	std::vector<int> numbers(10);
	std::iota(std::begin(numbers), std::end(numbers), 0);
	return numbers;
}

void TestIntVector() {
	const std::vector<int> numbers = MakeTestVector();
	{
		std::vector<int> numbers_copy = numbers;
		MakeJosephusPermutation(std::begin(numbers_copy), std::end(numbers_copy), 1);
		ASSERT_EQUAL(numbers_copy, numbers);
	}
	{
		std::vector<int> numbers_copy = numbers;
		MakeJosephusPermutation(std::begin(numbers_copy), std::end(numbers_copy), 3);
		ASSERT_EQUAL(numbers_copy, std::vector<int>({ 0, 3, 6, 9, 4, 8, 5, 2, 7, 1 }));
	}
}

struct NoncopyableInt {
	int value;

	NoncopyableInt(const NoncopyableInt&) = delete;
	NoncopyableInt& operator=(const NoncopyableInt&) = delete;

	NoncopyableInt(NoncopyableInt&&) = default;
	NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
	return lhs.value == rhs.value;
}

std::ostream& operator << (std::ostream& os, const NoncopyableInt& v) {
	return os << v.value;
}

void TestAvoidsCopying() {
	std::vector<NoncopyableInt> numbers;
	numbers.push_back({ 1 });
	numbers.push_back({ 2 });
	numbers.push_back({ 3 });
	numbers.push_back({ 4 });
	numbers.push_back({ 5 });

	MakeJosephusPermutation(begin(numbers), end(numbers), 2);

	std::vector<NoncopyableInt> expected;
	expected.push_back({ 1 });
	expected.push_back({ 3 });
	expected.push_back({ 5 });
	expected.push_back({ 4 });
	expected.push_back({ 2 });

	ASSERT_EQUAL(numbers, expected);
}


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	TestRunner tr;
	RUN_TEST(tr, TestIntVector);
	RUN_TEST(tr, TestAvoidsCopying);
	return 0;
}
