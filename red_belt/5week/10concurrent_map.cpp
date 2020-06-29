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

template <typename K, typename V>
class ConcurrentMap {
public:
    static_assert(std::is_integral_v<K>, "ConcurrentMap supports only integer keys");

    struct Access{
        ~Access(){
            mutex.unlock();
        }
        std::mutex& mutex;
        V& ref_to_value;
    };
    struct Bucket {
        std::mutex mutex;
        std::map<K, V> map_;
    };
    explicit ConcurrentMap(size_t bucket_count);
    Access operator[](const K& key);
    std::map<K, V> BuildOrdinaryMap();
private:
    std::vector<Bucket> buckets_;
};

template <typename K, typename V>
ConcurrentMap<K, V>::ConcurrentMap(size_t bucket_count){
    buckets_ = std::vector<Bucket>(bucket_count);
}


template <typename K, typename V>
typename ConcurrentMap<K, V>::Access ConcurrentMap<K, V>::operator[](const K& key){
    const size_t i = key % buckets_.size();
    buckets_[i].mutex.lock();
    if (buckets_[i].map_.count(key) == 0) {
        buckets_[i].map_.insert({ key, V() });
    }
    return { buckets_[i].mutex, buckets_[i].map_[key] };
}


template <typename K, typename V>
std::map<K, V> ConcurrentMap<K, V>::BuildOrdinaryMap(){
    std::map<K, V> result;
    for (size_t i = 0; i < buckets_.size(); ++i) {
        buckets_[i].mutex.lock();
        result.insert(buckets_[i].map_.begin(), buckets_[i].map_.end());
        buckets_[i].mutex.unlock();
    }
    return result;
}

void RunConcurrentUpdates(
    ConcurrentMap<int, int>& cm, size_t thread_count, int key_count
) {
    auto kernel = [&cm, key_count](int seed) {
        std::vector<int> updates(key_count);
        std::iota(begin(updates), end(updates), -key_count / 2);
        shuffle(begin(updates), end(updates), std::default_random_engine(seed));

        for (int i = 0; i < 2; ++i) {
            for (auto key : updates) {
                cm[key].ref_to_value++;
            }
        }
    };

    std::vector<std::future<void>> futures;
    for (size_t i = 0; i < thread_count; ++i) {
        futures.push_back(std::async(kernel, i));
    }
}

void TestConcurrentUpdate() {
    const size_t thread_count = 3;
    const size_t key_count = 50000;

    ConcurrentMap<int, int> cm(thread_count);
    RunConcurrentUpdates(cm, thread_count, key_count);

    const auto result = cm.BuildOrdinaryMap();
    ASSERT_EQUAL(result.size(), key_count);
    for (auto& [k, v] : result) {
        AssertEqual(v, 6, "Key = " + std::to_string(k));
    }
}

void TestReadAndWrite() {
    ConcurrentMap<size_t, std::string> cm(5);

    auto updater = [&cm] {
        for (size_t i = 0; i < 50000; ++i) {
            cm[i].ref_to_value += 'a';
        }
    };
    auto reader = [&cm] {
        std::vector<std::string> result(50000);
        for (size_t i = 0; i < result.size(); ++i) {
            result[i] = cm[i].ref_to_value;
        }
        return result;
    };

    auto u1 = std::async(updater);
    auto r1 = std::async(reader);
    auto u2 = std::async(updater);
    auto r2 = std::async(reader);

    u1.get();
    u2.get();

    for (auto f : { &r1, &r2 }) {
        auto result = f->get();
        ASSERT(all_of(result.begin(), result.end(), [](const std::string& s) {
            return s.empty() || s == "a" || s == "aa";
            }));
    }
}

void TestSpeedup() {
    {
        ConcurrentMap<int, int> single_lock(1);

        LOG_DURATION("Single lock");
        RunConcurrentUpdates(single_lock, 4, 50000);
    }
    {
        ConcurrentMap<int, int> many_locks(100);

        LOG_DURATION("100 locks");
        RunConcurrentUpdates(many_locks, 4, 50000);
    }
}


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
    TestRunner tr;
    RUN_TEST(tr, TestConcurrentUpdate);
    RUN_TEST(tr, TestReadAndWrite);
    RUN_TEST(tr, TestSpeedup);
	return 0;
}
