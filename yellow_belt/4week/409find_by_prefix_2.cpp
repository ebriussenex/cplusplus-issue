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
std::pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const std::string& prefix) {
	auto lower = std::lower_bound(range_begin, range_end, prefix);
	std::string temp = prefix;
	temp[temp.length() - 1]++;
	auto upper = std::lower_bound(range_begin, range_end, temp);
	return { lower, upper };
}

int main() {
	const std::vector<std::string> sorted_strings = { "moscow", "motovilikha", "murmansk" };

	const auto mo_result =
		FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
	for (auto it = mo_result.first; it != mo_result.second; ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	const auto mt_result =
		FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
	std::cout << (mt_result.first - begin(sorted_strings)) << " " <<
		(mt_result.second - begin(sorted_strings)) << std::endl;

	const auto na_result =
		FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
	std::cout << (na_result.first - begin(sorted_strings)) << " " <<
		(na_result.second - begin(sorted_strings)) << std::endl;

	return 0;
}

