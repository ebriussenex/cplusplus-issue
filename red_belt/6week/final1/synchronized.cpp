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
#include <mutex>
//#include <execution>
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

template <typename T>
class Synchronized {
public:
    explicit Synchronized(T init = T()) : value_(std::move(init)) {}
    struct Access
    {
        Access(T& value, std::mutex& mutex) : ref_to_value(value), guard_(mutex) {}
        T& ref_to_value;
    private:
        std::lock_guard<std::mutex> guard_;
    };
    Access GetAccess();
private:
    T value_;
    std::mutex mutex_;
};


template <typename T>
typename Synchronized<T>::Access Synchronized<T>::GetAccess()
{
    return { value_, mutex_ };
}

void TestConcurrentUpdate() {
    Synchronized<std::string> common_string;

    const size_t add_count = 50000;
    auto updater = [&common_string, add_count] {
        for (size_t i = 0; i < add_count; ++i) {
            auto access = common_string.GetAccess();
            access.ref_to_value += 'a';
        }
    };

    auto f1 = std::async(updater);
    auto f2 = std::async(updater);

    f1.get();
    f2.get();

    ASSERT_EQUAL(common_string.GetAccess().ref_to_value.size(), 2 * add_count);
}

std::vector<int> Consume(Synchronized<std::deque<int>>& common_queue) {
    std::vector<int> got;

    for (;;) {
        std::deque<int> q;

        {
            auto access = common_queue.GetAccess();
            q = std::move(access.ref_to_value);
        }

        for (int item : q) {
            if (item > 0) {
                got.push_back(item);
            }
            else {
                return got;
            }
        }
    }
}

void TestProducerConsumer() {
    Synchronized<std::deque<int>> common_queue;

    auto consumer = async(Consume, ref(common_queue));

    const size_t item_count = 100000;
    for (size_t i = 1; i <= item_count; ++i) {
        common_queue.GetAccess().ref_to_value.push_back(i);
    }
    common_queue.GetAccess().ref_to_value.push_back(-1);

    std::vector<int> expected(item_count);
    std::iota(begin(expected), end(expected), 1);
    ASSERT_EQUAL(consumer.get(), expected);
}


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
    TestRunner tr;
    RUN_TEST(tr, TestConcurrentUpdate);
    RUN_TEST(tr, TestProducerConsumer);
	return 0;
}
