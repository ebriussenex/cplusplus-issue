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
//#include "simple_vector.h"

//template <typename T>
//class ObjectId {
//public:
//	ObjectId() = default;
//	friend bool operator<(const ObjectId& lhs, const ObjectId& rhs) {
//		return lhs.id < rhs.id;
//	}
//	friend bool operator==(const ObjectId& lhs, const ObjectId& rhs) {
//		return lhs.id == rhs.id && lhs.priority == rhs.priority;
//	}
//	friend bool operator<=(const ObjectId& lhs, const ObjectId& rhs) {
//		return lhs.id <= rhs.id;
//	}
//	Id GetId() const {
//		return id;
//	}
//private:
//	Priority priority = 0;
//	Id id;
//};
//
//template <typename T>
//class Object {
//public:
//	Object() = default;
//	Priority GetPriority() const{
//		return priority;
//	}
//	T GetItem() const {
//		return item;
//	}
//private:
//	Priority priority = 0;
//	T item;
//};

template <typename T>
class PriorityCollection {
public:

	using Id = int;
	using Priority = int;

	Id Add(T object) {
		const Id id = objects_.size();
		objects_.push_back({ std::move(object) });
		sorted_ids_info_.insert({ 0, id });
		return id;
	}

	template <typename ObjInputIt, typename IdOutputIt>
	void Add(ObjInputIt range_begin, ObjInputIt range_end,
		IdOutputIt ids_begin) {
		while (range_begin != range_end) {
			*ids_begin++ = Add(std::move(*range_begin++));
		}
	}

	bool IsValid(Id id) const {
		return id >= 0 && id < objects_.size() && objects_[id].priority_ >= 0;
	}

	const T& Get(Id id) const {
		return objects_[id].item_;
	}


	void Promote(Id id) {
		const auto& item = objects_[id];
		const auto old_prior = item.priority_;
		const auto new_prior = old_prior + 1;
		objects_[id].priority_ = new_prior;
		sorted_ids_info_.erase({ old_prior, id });
		sorted_ids_info_.insert({ new_prior, id });
	}

	
	std::pair<const T&, int> GetMax() const {
		const auto& max_item = objects_[(std::prev(sorted_ids_info_.end()))->second];
		return { max_item.item_, max_item.priority_ };
	}

	std::pair<T, int> PopMax() {
		const auto max_item_info = std::prev(sorted_ids_info_.end());
		Id max_item_id = max_item_info->second;
		Object& max_item = objects_[max_item_id];
		sorted_ids_info_.erase({ max_item.priority_, max_item_id });
		int temp_pr = objects_[max_item_id].priority_;
		objects_[max_item_id].priority_ = -1;
		return std::make_pair(std::move(max_item.item_), temp_pr);
	}

private:
	struct Object {
		T item_;
		Priority priority_ = 0;
	};
	std::vector<Object> objects_;
	std::set<std::pair<Priority, Id>> sorted_ids_info_;
};


class StringNonCopyable : public std::string {
public:
	using std::string::string;  // ѕозвол€ет использовать конструкторы строки
	StringNonCopyable(const StringNonCopyable&) = delete;
	StringNonCopyable(StringNonCopyable&&) = default;
	StringNonCopyable& operator=(const StringNonCopyable&) = delete;
	StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
	PriorityCollection<StringNonCopyable> strings;
	const auto white_id = strings.Add("white");
	const auto yellow_id = strings.Add("yellow");
	const auto red_id = strings.Add("red");

	strings.Promote(yellow_id);
	for (int i = 0; i < 2; ++i) {
		strings.Promote(red_id);
	}
	strings.Promote(yellow_id);
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "red");
		ASSERT_EQUAL(item.second, 2);
	}
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "yellow");
		ASSERT_EQUAL(item.second, 2);
	}
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "white");
		ASSERT_EQUAL(item.second, 0);
	}
}



int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	TestRunner tr;
	RUN_TEST(tr, TestNoCopy);
	return 0;
}
