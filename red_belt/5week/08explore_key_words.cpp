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
#include <future>
#include <thread>

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
//#include "simple_vector.h"

using Matrix = std::vector<std::vector<int>>;

template <typename Iterator>
class IteratorRange {
public:
	IteratorRange(Iterator begin, Iterator end)
		: first_(begin)
		, last_(end)
		, size_(std::distance(first_, last_))
	{
	}
	void assign_first(Iterator first) {
		first_ = first;
	}
	void assign_last(Iterator last) {
		last_ = last;
	}
	Iterator begin() const {
		return first_;
	}

	Iterator end() const {
		return last_;
	}

	size_t size() const {
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
	Paginator<Iterator>(const Iterator& begin, const Iterator& end, const size_t& page_size) {
		auto page_size_ = page_size;
		auto page_begin = begin;
		auto page_end = page_begin;
		while (page_end < end) {
			size_t div = end - page_begin;
			auto diff = std::min(page_size, div);
			page_end = page_begin + diff;
			pages_.push_back({ page_begin, page_end });
			page_begin = page_end;
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
	std::vector<IteratorRange<Iterator>> pages_;
};


template <typename C>
auto Paginate(C& c, size_t page_size) {
	return Paginator(c.begin(), c.end(), page_size);
}

struct Stats {
	std::map<std::string, int> word_frequences;
	void operator+=(const Stats& other) {
		for (const auto& [word, number_of_occurrences] : other.word_frequences) {
			word_frequences[word] += number_of_occurrences;
		}
	}
};

Stats ExploreLine(const std::set<std::string>& key_words, const std::string& line) {
	Stats lines;
	std::stringstream ss{ line };
	for (std::string word; ss >> word;) {
		if (key_words.count(word) > 0) {
			++lines.word_frequences[word];
		}
	}
	return lines;
}

Stats ExploreKeyWordsSingleThread(
	const std::set<std::string>& key_words, std::istream& input
) {
	Stats result;
	for (std::string line; std::getline(input, line); ) {
		result += ExploreLine(key_words, line);
	}
	return result;
}

Stats ExploreKeyWords(const std::set<std::string>& key_words, std::istream& input) {
	std::vector<std::future<Stats>> futures;
	std::vector<std::string> lines;
	for (std::string line; std::getline(input, line);) {
		lines.push_back(line);
	}

	std::deque<std::stringstream> streams;
	for (auto& page : Paginate(lines, (lines.size() + 3) / 4)) {
		std::stringstream in;
		for (std::string& line : page) {
			in << line << '\n';
		}
		streams.push_back(std::move(in));
		futures.push_back(std::async(ExploreKeyWordsSingleThread, ref(key_words), ref(streams.back())));
	}

	Stats line_stats;
	for (std::future<Stats>& stat : futures) {
		line_stats += stat.get();
	}
	return line_stats;
}

void TestBasic() {
	const std::set<std::string> key_words = { "yangle", "rocks", "sucks", "all" };

	std::stringstream ss;
	ss << "this new yangle service really rocks\n";
	ss << "It sucks when yangle isn't available\n";
	ss << "10 reasons why yangle is the best IT company\n";
	ss << "yangle rocks others suck\n";
	ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

	const auto stats = ExploreKeyWords(key_words, ss);
	const std::map<std::string, int> expected = {
	  {"yangle", 6},
	  {"rocks", 2},
	  {"sucks", 1}
	};
	ASSERT_EQUAL(stats.word_frequences, expected);
}



int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	TestRunner tr;
	RUN_TEST(tr, TestBasic);
	return 0;
}
