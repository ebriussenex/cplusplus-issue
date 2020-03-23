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


void TestCopyAssignment() {
	SimpleVector<int> numbers(10);
	std::iota(numbers.begin(), numbers.end(), 1);

	SimpleVector<int> dest;
	ASSERT_EQUAL(dest.Size(), 0u);

	dest = numbers;
	ASSERT_EQUAL(dest.Size(), numbers.Size());
	ASSERT(dest.Capacity() >= dest.Size());
	ASSERT(std::equal(dest.begin(), dest.end(), numbers.begin()));
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	TestRunner tr;
	RUN_TEST(tr, TestCopyAssignment);
	return 0;
}
