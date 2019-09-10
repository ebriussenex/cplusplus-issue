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

// Реализуйте здесь шаблонный класс Table
template <typename T>
class Table {
public:
	Table(size_t line_number, size_t column_number) {
		Resize(line_number, column_number);
	}
	void Resize(size_t new_line_number, size_t new_column_number) {
		table_.resize(new_line_number);
		for (auto& item : table_) {
			item.resize(new_column_number);
		}
		line_number_ = new_line_number;
		column_number_ = new_column_number;
	}
	const std::vector<T>& operator [](size_t i) const{
		return table_[i];
	}
	std::vector<T>& operator [](size_t i) {
		return table_[i];
	}
	std::pair<size_t, size_t> Size() const {
		return std::make_pair(line_number_, column_number_);
	}
private:
	size_t line_number_;
	size_t column_number_;
	std::vector<std::vector<T>> table_;
};

void TestTable() {
	Table<int> t(1, 1);
	ASSERT_EQUAL(t.Size().first, 1u);
	ASSERT_EQUAL(t.Size().second, 1u);
	t[0][0] = 42;
	ASSERT_EQUAL(t[0][0], 42);
	t.Resize(3, 4);
	ASSERT_EQUAL(t.Size().first, 3u);
	ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestTable);
	return 0;
}
