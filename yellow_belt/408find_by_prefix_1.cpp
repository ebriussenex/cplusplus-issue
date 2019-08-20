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
#include <numeric>

#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <functional>

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
	auto lower = std::lower_bound(range_begin, range_end, std::string(1, prefix));
	auto upper = std::upper_bound(range_begin, range_end, std::string(1, static_cast<char>(prefix + 1)));
	return { lower, upper };
}

int main() {
	const std::vector<std::string> sorted_strings = { "moscow", "murmansk", "vologda" };

	const auto m_result =
		FindStartsWith(std::begin(sorted_strings), std::end(sorted_strings), 'm');
	for (auto it = m_result.first; it != m_result.second; ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	const auto p_result =
		FindStartsWith(std::begin(sorted_strings), std::end(sorted_strings), 'p');
	std::cout << (p_result.first - std::begin(sorted_strings)) << " " <<
		(p_result.second - std::begin(sorted_strings)) << std::endl;

	const auto z_result =
		FindStartsWith(std::begin(sorted_strings), std::end(sorted_strings), 'z');
	std::cout << (z_result.first - std::begin(sorted_strings)) << " " <<
		(z_result.second - std::begin(sorted_strings)) << std::endl;

	return 0;
}

