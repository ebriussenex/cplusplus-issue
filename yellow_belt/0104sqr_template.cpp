#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>
#include <exception>
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

template <typename T> T Sqr(T x);
template <typename Item> std::vector<Item> operator* (const std::vector <Item>& lv, const std::vector <Item>& rv);
template <typename First, typename Second> std::pair<First, Second> operator* (const std::pair <First, Second> lp, const std::pair<First, Second> rp);
template <typename Key, typename Value> std::map<Key, Value> operator* (const std::map <Key, Value>& lm, const std::map <Key, Value>& rm);

template <typename T>
T Sqr(T x) {
	return x * x;
}

template <typename Item>
std::vector<Item> operator* (const std::vector <Item>& lv, const std::vector <Item>& rv) {
	std::vector <Item> ans;
	for (size_t i = 0; i < lv.size(); i++) {
		ans.push_back(lv[i] * rv[i]);
	}
	return ans;
}

template <typename First, typename Second> 
std::pair<First, Second> operator* (const std::pair <First, Second> lp, const std::pair<First, Second> rp) {
	return std::make_pair(lp.first * rp.first, lp.second * rp.second);
}

template <typename Key, typename Value> 
std::map<Key, Value> operator* (const std::map <Key, Value>& lm, const std::map <Key, Value>& rm) {
	std::map <Key, Value> ans;
	for (std::pair<Key, Value> item : lm) {
		ans[item.first] = lm.at(item.first) * rm.at(item.first);
	}
	return ans;
}

int main() {
	std::vector<int> v = { 1, 2, 3 };
	std::cout << "vector:";
	for (int x : Sqr(v)) {
		std::cout << ' ' << x;
	}
	std::cout << std::endl;

	std::map<int, std::pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	std::cout << "map of pairs:" << std::endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		std::cout << x.first << ' ' << x.second.first << ' ' << x.second.second << std::endl;
	}
	return 0;
}