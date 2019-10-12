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
#include "profile.h"

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int its_num, other_num;
	int sportsman_count;
	std::cin >> sportsman_count;
	std::list<int> row;
	std::vector<std::list<int>::iterator> numbers(100'001, row.end());
	for (size_t i = 0; i < sportsman_count; i++) {
		std::cin >> its_num >> other_num;
		numbers[its_num] = row.insert(numbers[other_num], its_num);
	}
	for (const auto item : row) {
		std::cout << item << "\n";
	}
	return 0;
}