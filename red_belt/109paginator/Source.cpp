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
template<typename Iterator>
class IteratorRange {
public:
	IteratorRange() {}
	IteratorRange(Iterator first, Iterator last) :
		first_(first), last_(last), size_(std::distance(first, last)) {
	}
	Iterator begin() const {
		return first_;
	}
	Iterator end() const {
		return last_;
	}

	Iterator size() const {
		return size_;
	}
private:
	Iterator first_;
	Iterator last_;
	size_t size_;
};

template <typename Iterator>
class Paginator {
public:
	Paginator<Iterator>(const Iterator& begin, const Iterator& end, const size_t& page_size)/* :
		begin_(begin), end_(end), page_size_(page_size) */ {
		if (std::distance(begin, end) <= page_size_) {
			pages_.push_back({ begin, end });
		}
		else {
			auto page_begin = begin;
			auto page_end = begin;
			while (page_begin - end >= page_size) {
				pages_.push_back({ page_begin, std::advance(page_begin, page_size) });
			}
			pages_.push_back({ page_begin, end });
		}
	}
	auto begin() const {
		return pages_.begin();
	}
	auto end() const {
		return pages_.end();
	}

	size_t size() const {
		return pages_.size();
	}
private:
	Iterator begin_;
	Iterator end_;
	size_t page_size_;
	std::vector<IteratorRange<Iterator>> pages_;
};


template <typename C>
auto Paginate(C& c, size_t page_size) {
	return Paginator(c.begin(), c.end(), page_size);
}

void TestPageCounts() {
	std::vector<int> v(15);

	ASSERT_EQUAL(Paginate(v, 1).size(), v.size());
	ASSERT_EQUAL(Paginate(v, 3).size(), 5u);
	ASSERT_EQUAL(Paginate(v, 5).size(), 3u);
	ASSERT_EQUAL(Paginate(v, 4).size(), 4u);
	ASSERT_EQUAL(Paginate(v, 15).size(), 1u);
	ASSERT_EQUAL(Paginate(v, 150).size(), 1u);
	ASSERT_EQUAL(Paginate(v, 14).size(), 2u);
}

void TestLooping() {
	std::vector<int> v(15);
	std::iota(begin(v), end(v), 1);

	Paginator<std::vector<int>::iterator> paginate_v(v.begin(), v.end(), 6);
	std::ostringstream os;
	for (const auto& page : paginate_v) {
		for (int x : page) {
			os << x << ' ';
		}
		os << '\n';
	}

	ASSERT_EQUAL(os.str(), "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n");
}

void TestModification() {
	std::vector<std::string> vs = { "one", "two", "three", "four", "five" };
	for (auto page : Paginate(vs, 2)) {
		for (auto& word : page) {
			word[0] = toupper(word[0]);
		}
	}

	const std::vector<std::string> expected = { "One", "Two", "Three", "Four", "Five" };
	ASSERT_EQUAL(vs, expected);
}

void TestPageSizes() {
	std::string letters(26, ' ');

	Paginator letters_pagination(letters.begin(), letters.end(), 11);
	std::vector<size_t> page_sizes;
	for (const auto& page : letters_pagination) {
		page_sizes.push_back(page.size());
	}

	const std::vector<size_t> expected = { 11, 11, 4 };
	ASSERT_EQUAL(page_sizes, expected);
}

void TestConstContainer() {
	const std::string letters = "abcdefghijklmnopqrstuvwxyz";

	std::vector<std::string> pages;
	for (const auto& page : Paginate(letters, 10)) {
		pages.push_back(std::string(page.begin(), page.end()));
	}

	const std::vector<std::string> expected = { "abcdefghij", "klmnopqrst", "uvwxyz" };
	ASSERT_EQUAL(pages, expected);
}

void TestPagePagination() {
	std::vector<int> v(22);
	std::iota(begin(v), end(v), 1);

	std::vector<std::vector<int>> lines;
	for (const auto& split_by_9 : Paginate(v, 9)) {
		for (const auto& split_by_4 : Paginate(split_by_9, 4)) {
			lines.push_back({});
			for (int item : split_by_4) {
				lines.back().push_back(item);
			}
		}
	}

	const std::vector<std::vector<int>> expected = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9},
		{10, 11, 12, 13},
		{14, 15, 16, 17},
		{18},
		{19, 20, 21, 22}
	};
	ASSERT_EQUAL(lines, expected);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestPageCounts);
	RUN_TEST(tr, TestLooping);
	RUN_TEST(tr, TestModification);
	RUN_TEST(tr, TestPageSizes);
	RUN_TEST(tr, TestConstContainer);
	RUN_TEST(tr, TestPagePagination);
}