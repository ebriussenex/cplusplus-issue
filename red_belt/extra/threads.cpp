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

template <typename ContainerOfVectors>
void GenerateSingleThread(ContainerOfVectors& result, size_t first_row, size_t column_size) {
	for (auto& row : result) {
		row.reserve(column_size);
		for (size_t column = 0; column < column_size; column++) {
			row.push_back(first_row ^ column);
		}
		++first_row;
	}
}

Matrix GenerateSingleThread(size_t size) {
	Matrix result(size);
	GenerateSingleThread(result, 0, size);
	return result;
}

Matrix GenerateMultiThread(
	size_t size, size_t page_size
) {
	Matrix result(size);
	std::vector <std::future <void >> futures;
	size_t first_row = 0;
	for (auto page : Paginate(result, page_size)) {
		futures.push_back(
			std::async([page, first_row, size] {
				GenerateSingleThread(page, first_row, size);
				})
		);
		first_row += page_size;
	}
	return result;
}


template <typename ContainerOfVectors>
int64_t SumSingleThread(const ContainerOfVectors& matrix) {
	int64_t sum = 0;
	for (const auto& row : matrix) {
		for (auto item : row) {
			sum += item;
		}
	}
	return sum;
}

int SumOfTwoVec(const std::vector<int>& lhs, const std::vector<int>& rhs) {
	std::future<int> f = std::async([&lhs] {return std::accumulate(lhs.begin(), lhs.end(), 0); });
	int result = std::accumulate(rhs.begin(), rhs.end(), 0);
	return result + f.get();
}

int64_t CalculateMatrixSum(const Matrix& matrix) {
	int64_t result = 0;
	std::vector <std::future <int64_t >> futures;
	for (auto page : Paginate(matrix, 2000)) {
		futures.push_back(
			std::async([page] {return SumSingleThread(page); })
		);
	}
	for (auto& f : futures) {
		result += f.get();
	}
	return result;
}

void TestCalculateMatrixSum() {
	const std::vector<std::vector<int>> matrix = {
	  {1, 2, 3, 4},
	  {5, 6, 7, 8},
	  {9, 10, 11, 12},
	  {13, 14, 15, 16}
	};
	ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}



int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	/*LOG_DURATION("TOTAL");
	const size_t matrix_size = 7000;
	const size_t page_size = 2000;

	std::vector <std::vector<int>> matrix;
	{
		LOG_DURATION("Single thread generation");
		matrix = GenerateSingleThread(matrix_size);
	}
	{
		LOG_DURATION("Multi thread generation");
		matrix = GenerateMultiThread(matrix_size, page_size);
	}
	{
		LOG_DURATION("Single thread sum");
		std::cout << SumSingleThread(matrix) << std::endl;
	}*/
	TestRunner tr;
	RUN_TEST(tr, TestCalculateMatrixSum);
	return 0;
}
