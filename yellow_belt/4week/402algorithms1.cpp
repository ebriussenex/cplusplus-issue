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

void PrintVectorPart(const std::vector<int> & numbers) {
	auto it = find_if(numbers.begin(), numbers.end(), [](int x) { return x < 0; });
	bool first = true;
	while (it > numbers.begin()) {
		--it;
		if (!first) std::cout << " ";
		std::cout << *it;
		first = false;
	}
}

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T>& elements, const T& border) {
	auto it = lower_bound(elements.begin(), elements.end(), border);
	if (it != elements.end() && *it <= border) {
		it++;
	}
	return { it, elements.end() };
}

std::vector<std::string> SplitIntoWords(const std::string& s) {
	auto it = s.begin();
	std::vector<std::string> ret;
	auto itt = find(s.begin(), s.end(), ' ');
	if (itt == s.end()) ret.push_back(s);
	while (itt != s.end()) {
		itt = find(it, s.end(), ' ');
		ret.push_back({ it, itt });
		if (itt == s.end()--) itt = s.end();
		else itt++;
		it = itt;
	}
	return ret;
}

template <typename T>
void RemoveDuplicates(std::vector<T>& elements) {
	std::set <T> s;
	std::copy(elements.begin(), elements.end(), std::inserter(s, s.end()));
	elements.assign(s.begin(), s.end());
}

int main() {
	int n;
	std::cin >> n;
	std::vector <int> v(n);
	std::iota(v.begin(), v.end(), 1);
	sort(v.rbegin(), v.rend());
	do {
		bool first = true;
		for (const auto& i : v) {
			if(!first) std::cout << ' ' << i;
			else std::cout << i;
			first = false;
		}
		std::cout << std::endl;
	} while (std::prev_permutation(v.begin(), v.end()));
	return 0;
}
