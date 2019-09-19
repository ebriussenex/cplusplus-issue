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
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (range_end - range_begin < 2) return;
	std::vector<typename RandomIt::value_type> v(range_begin, range_end);
	auto it1 = v.begin() + v.size() / 3;
	auto it2 = v.begin() + 2 * (v.size() / 3);
	MergeSort(v.begin(), it1);
	MergeSort(it1, it2);
	MergeSort(it2, v.end());
	std::vector<typename RandomIt::value_type> temp;
	std::merge(v.begin(), it1, it1, it2, std::back_inserter(temp));
	std::merge(temp.begin(), temp.end(), it2, v.end(), range_begin);
	/*auto it = v.begin() + v.size() / 2;
	MergeSort(v.begin(), it);
	MergeSort(it, v.end());
	std::merge(v.begin(), it, it, v.end(), range_begin);*/
}
int main() {
	std::vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1, 5 };
	MergeSort(begin(v), end(v));
	for (int x : v) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	return 0;
}


