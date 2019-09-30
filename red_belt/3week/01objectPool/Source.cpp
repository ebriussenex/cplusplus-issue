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

template <class T>
class ObjectPool {
public:
	ObjectPool() {
	}
	T* Allocate() {
		if (data_free_.empty()) {
			data_free_.push(new T);
		}
		auto data = data_free_.front();
		data_allocated_.insert(data);
		data_free_.pop();
		return *data_allocated_.find(data);
	}
	T* TryAllocate() {
		if (data_free_.empty()) {
			return nullptr;
		}
		auto data = data_free_.front();
		data_allocated_.insert(data);
		data_free_.pop();
		return *data_allocated_.find(data);
	}

	void Deallocate(T* object) {
		auto it = data_allocated_.find(object);
		if (it == data_allocated_.end()) {
			throw std::invalid_argument("");
		}
		else {
			data_free_.push(*it);
			data_allocated_.erase(it);
		}
	}

	~ObjectPool() {
		for (auto item : data_allocated_) {
			delete item;
		}
		while (!data_free_.empty()) {
			auto temp = data_free_.front();
			delete temp;
			data_free_.pop();
		}
	}

private:
	std::set<T*> data_allocated_;
	std::queue<T*> data_free_;
};

void TestObjectPool() {
	ObjectPool<std::string> pool;

	auto p1 = pool.Allocate();
	auto p2 = pool.Allocate();
	auto p3 = pool.Allocate();
	*p1 = "first";
	*p2 = "second";
	*p3 = "third";

	pool.Deallocate(p2);
	ASSERT_EQUAL(*pool.Allocate(), "second");

	pool.Deallocate(p3);
	pool.Deallocate(p1);
	ASSERT_EQUAL(*pool.Allocate(), "third");
	ASSERT_EQUAL(*pool.Allocate(), "first");

	pool.Deallocate(p1);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestObjectPool);
	return 0;
}