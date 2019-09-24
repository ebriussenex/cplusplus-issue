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

class Learner {
private:
	std::set<std::string> dict;

public:
	int Learn(const std::vector<std::string>& words) {
		LOG_DURATION("learn");
		std::set<std::string> s = std::set<std::string>(words.begin(), words.end());
		auto temp = dict.size();
		for (const auto& item : s) {
			dict.insert(item);
		}
		return dict.size() - temp;
		/*std::set<std::string> s = std::set<std::string>(words.begin(), words.end());
		int temp = dict.size();
		for (const auto& item : s) {
			dict.push_back(item);
		}
		std::set<std::string> sb = std::set<std::string>(dict.begin(), dict.end());
		dict = std::vector<std::string>(sb.begin(), sb.end());
		return dict.size() - temp;*/
		/*std::set<std::string> s = std::set<std::string>(words.begin(), words.end());
		std::set<std::string> sb = std::set<std::string>(dict.begin(), dict.end());
		for (const auto& item : s) {
			sb.insert(item);
		}
		int temp = dict.size();
		dict = std::vector<std::string>(sb.begin(), sb.end());
		return dict.size() - temp;*/
	}

	std::vector<std::string> KnownWords() {
		return std::vector<std::string>(dict.begin(), dict.end());
	}
};

void TestLearnDuration(){
	Learner learner;
	std::string line = "a b c d e f g h i j k l m n o p q r s t u v w x y z 1 2 3 4 5 6 7 8 9 0 aa bb cc dd ss wdwd awa  sdf asdff aasd ffda fasd";
	std::stringstream ss(line);
	std::string word;
	std::vector<std::string> words;
	while (ss >> word) {
		words.push_back(word);
	}
	std::cout << learner.Learn(words) << "\n";
	std::cout << "=== known words ===\n";
	for (auto word : learner.KnownWords()) {
		std::cout << word << "\n";
	}
}

int main() {
	LOG_DURATION("start");
	TestRunner tr;
	TestLearnDuration();
	return 0;
}