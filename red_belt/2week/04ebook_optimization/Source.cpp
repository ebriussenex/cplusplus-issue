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


class ReadingManager {
public:
	ReadingManager() :
		users_on_page_(100001, 0)
	{}

	void Read(const int& user_id, const int& page_count) {
		if (!user_page_.count(user_id)) {
			user_page_[user_id] = page_count;
			users_on_page_[page_count]++;
		}
		else{
			int temp = user_page_.at(user_id);
			user_page_[user_id] = page_count;
			users_on_page_[page_count]++;
			users_on_page_[temp]--;
		}
	}

	double Cheer(const int& user_id) const {
		if (!user_page_.count(user_id)) {//if he is enlisted or have read 0 pages
			return 0;
		}
		if (user_page_.size() == 1) return 1;
		else {
			int user_s_page = user_page_.at(user_id);
			double users_less = 0;
			for (size_t i = 0; i < user_s_page; i++) {
				users_less += users_on_page_[i];
			}
			return users_less / static_cast<double>(user_page_.size() - 1);
		}
	}

private:
	std::map<int, int> user_page_;
	std::vector<int> users_on_page_;
};



int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	ReadingManager manager;

	int query_count;
	std::cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		std::string query_type;
		std::cin >> query_type;
		int user_id;
		std::cin >> user_id;

		if (query_type == "READ") {
			int page_count;
			std::cin >> page_count;
			manager.Read(user_id, page_count);
		}
		else if (query_type == "CHEER") {
			std::cout << std::setprecision(6) << manager.Cheer(user_id) << "\n";
		}
	}
	return 0;
}