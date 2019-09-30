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

template <typename T>
class SimpleVector {
public:
	explicit SimpleVector(const size_t& size) {
		data_ = new T[size];
		end_ = data_ + size;
	}
	~SimpleVector() {
		delete[] data_;
	}
	T& operator(const size_t& index) {
		return data[index];//return *(data_ + index);
	}

	const T* begin() const { return data_; }
	const T* end() const { return end_; }
	T* begin() const { return data_; }
	T* end() const { return end_; }
private:
	T* data_;
	T* end_;
};

template <typename T>
void Print(const SimpleVector<T>& sv) {

}

int main() {

	return 0;
}
