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

std::vector<std::string> SplitIntoWords(const std::string & str) {
	std::vector<std::string> result;
	auto str_begin = str.begin();
	auto str_end = str.end();
	while (true) {
		auto it = std::find(str_begin, str_end, ' ');
		result.push_back(std::string(str_begin, it));
		if (it == str_end) break;
		else str_begin = it + 1;
	}
	return result;
}

std::vector<std::string_view> SplitIntoWordsView(const std::string_view& s) {
	std::string_view  str = s;
	std::vector<std::string_view> result;
	while (true) {
		size_t space = str.find(' ');
		result.push_back(str.substr(0, space));
		if (space == str.npos) break;
		else str.remove_prefix(space + 1);
	}
	return result;
}

std::string GenerateText() {
	const int SIZE = 1000000;
	std::string text(SIZE, 'a');
	for (int i = 100; i < SIZE; i += 100) {
		text[i] = ' ';
	}
	return text;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	const std::string text = GenerateText();
	{ LOG_DURATION("string");
	const auto words = SplitIntoWords(text);
	std::cout << words[0] << "\n";
	}
	{ LOG_DURATION("string_view");
	const auto words = SplitIntoWordsView(text);
	std::cout << words[0] << "\n";
	}

	return 0;
}