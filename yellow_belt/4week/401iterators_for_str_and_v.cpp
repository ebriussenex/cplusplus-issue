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

int main() {
	std::string s = "C Cpp Java Python";

	std::vector<std::string> words = SplitIntoWords(s);
	std::cout << words.size() << " ";
	for (auto it = begin(words); it != end(words); ++it) {
		if (it != begin(words)) {
			std::cout << "/";
		}
		std::cout << *it;
	}
	std::cout << std::endl;

	return 0;
}

