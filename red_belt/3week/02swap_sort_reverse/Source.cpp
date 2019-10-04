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

//template <typename T>
//class SimpleVector {
//public:
//	explicit SimpleVector(const size_t& size) {
//		data_ = new T[size];
//		end_ = data_ + size;
//	}
//	~SimpleVector() {
//		delete[] data_;
//	}
//	T& operator(const size_t& index) {
//		return data[index];//return *(data_ + index);
//	}
//
//	const T* begin() const { return data_; }
//	const T* end() const { return end_; }
//	T* begin() const { return data_; }
//	T* end() const { return end_; }
//private:
//	T* data_;
//	T* end_;
//};
//
//template <typename T>
//void Print(const SimpleVector<T>& sv) {
//
//}

template <typename T>
void Swap(T* first, T* second) {
	auto temp = *first;
	*first = *second;
	*second = temp;
}

template <typename T>
void SortPointers(std::vector<T*>& pointers) {
	std::sort(pointers.begin(), pointers.end(), [](T* lhs, T* rhs) {return *lhs < *rhs; });
}

template <typename T>
void ReversedCopy(T* src, const size_t& count, T* dst) {
	auto first_begin = src;
	auto first_end = src + count;
	auto second_begin = dst;
	auto second_end = dst + count;
	if (second_begin >= first_end || second_end <= first_begin) {
		std::reverse_copy(first_begin, first_end, second_begin);
	}
	else if (second_begin > first_begin) {
		for (size_t i = 0; first_begin + i < second_begin; ++i) {
			*(second_end - i - 1) = *(first_begin + i);
		}
		std::reverse(second_begin, first_end);
	}
	else {
		for (size_t i = 0; first_end - i - 1 >= second_end; ++i) {
			*(second_begin + i) = *(first_end - i - 1);
		}
		std::reverse(first_begin, second_end);
	}
}

void TestSwap() {
	int a = 1;
	int b = 2;
	Swap(&a, &b);
	ASSERT_EQUAL(a, 2);
	ASSERT_EQUAL(b, 1);

	std::string h = "world";
	std::string w = "hello";
	Swap(&h, &w);
	ASSERT_EQUAL(h, "hello");
	ASSERT_EQUAL(w, "world");
}

void TestSortPointers() {
	int one = 1;
	int two = 2;
	int three = 3;

	std::vector<int*> pointers;
	pointers.push_back(&two);
	pointers.push_back(&three);
	pointers.push_back(&one);

	SortPointers(pointers);

	ASSERT_EQUAL(pointers.size(), 3u);
	ASSERT_EQUAL(*pointers[0], 1);
	ASSERT_EQUAL(*pointers[1], 2);
	ASSERT_EQUAL(*pointers[2], 3);
}

void TestReverseCopy() {
	const size_t count = 7;

	int* source = new int[count];
	int* dest = new int[count];

	for (size_t i = 0; i < count; ++i) {
		source[i] = i + 1;
	}
	ReversedCopy(source, count, dest);
	const std::vector<int> expected1 = { 7, 6, 5, 4, 3, 2, 1 };
	ASSERT_EQUAL(std::vector<int>(dest, dest + count), expected1);

	// Области памяти могут перекрываться
	ReversedCopy(source, count - 1, source + 1);
	const std::vector<int> expected2 = { 1, 6, 5, 4, 3, 2, 1 };
	ASSERT_EQUAL(std::vector<int>(source, source + count), expected2);

	delete[] dest;
	delete[] source;
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSwap);
	RUN_TEST(tr, TestSortPointers);
	RUN_TEST(tr, TestReverseCopy);
	return 0;
}