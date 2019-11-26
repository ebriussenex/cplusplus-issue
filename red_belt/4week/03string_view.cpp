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

class Translator {
public:
	Translator() {}
	void Add(std::string_view source, std::string_view target) {
		const std::string_view source_view = GetClonedView(source);
		const std::string_view target_view = GetClonedView(target);
		forward_[source_view] = target_view;
		backward_[target_view] = source_view;
	}
	std::string_view TranslateForward(std::string_view source) const {
		auto it = forward_.find(source);
		if (it == forward_.end()) return "";
		else return it->second;
	}
	std::string_view TranslateBackward(std::string_view target) const {
		auto it = backward_.find(target);
		if (it == backward_.end()) return "";
		else return it->second;
	}
private:
	std::string_view GetClonedView(std::string_view s) {
		for (const auto* map_ptr : { &forward_, &backward_ }) {
			const auto it = map_ptr->find(s);
			if (it != map_ptr->end()) {
				return it->first;
			}
		}
		return data_.emplace_back(s);
	}
	std::list <std::string> data_;
	std::map<std::string_view, std::string_view> forward_;
	std::map<std::string_view, std::string_view> backward_;
};

//void TestSimple() {
//	Translator translator;
//	translator.Add(std::string("okno"), std::string("window"));
//	translator.Add(std::string("stol"), std::string("table"));
//
//	ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
//	ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
//	ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
//}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	/*TestRunner tr;
	RUN_TEST(tr, TestSimple);*/
	return 0;
}