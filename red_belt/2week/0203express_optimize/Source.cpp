#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <cstdint>
#include <memory>

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

class RouteManager {
public:
	void AddRoute(int start, int finish) {
		reachable_lists_[start].insert(finish);
		reachable_lists_[finish].insert(start);
	}
	int FindNearestFinish(const int& start, const int& finish) const {
		int result = std::abs(start - finish);
		if (reachable_lists_.count(start) < 1) {
			return result;
		}
		if (!reachable_lists_.at(start).empty()) {
			const std::set<int>& reachable_stations = reachable_lists_.at(start);
			const auto it = reachable_stations.lower_bound(finish);
			if (it != reachable_stations.end()) {
				result = std::min(result, std::abs(finish - *it));
			}
			if (it != reachable_stations.begin()) {
				result = std::min(result, std::abs(finish - *std::prev(it)));
			}
		}
		/*const std::set<int>& reachable_stations = reachable_lists_.at(start);
		if (!reachable_stations.empty()) {
			result = std::min(
				result,
				abs(finish - *std::min_element(
					reachable_stations.begin(), reachable_stations.end(),
					[finish](int lhs, int rhs) { return abs(lhs - finish) < abs(rhs - finish); }
				))
			);
		}*/
		return result;
	}
private:
	std::map<int, std::set<int>> reachable_lists_;
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	RouteManager routes;

	int query_count;
	std::cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		std::string query_type;
		std::cin >> query_type;
		int start, finish;
		std::cin >> start >> finish;
		if (query_type == "ADD") {
			routes.AddRoute(start, finish);
		}
		else if (query_type == "GO") {
			std::cout << routes.FindNearestFinish(start, finish) << "\n";
		}
	}
	return 0;
}