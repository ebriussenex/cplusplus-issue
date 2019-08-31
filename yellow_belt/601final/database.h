#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>
#include <stdexcept>
#include <exception>
#include <algorithm>
#include <functional>

#include "date.h"

using Db = std::map<Date, std::set<std::string>>;
using DbLast = std::map<Date, std::vector<std::string>>;

class Database {
public:
	Database() {};
	void Add(const Date& date, const std::string& event);
	void Print(std::ostream& os) const;

	template <typename Func>
	int RemoveIf(Func predicate) {
		unsigned int size_to_del = 0, count = 0;
		for (auto& row : db_for_last_) {//deletes events due to condition
			Date date = row.first;
			auto it = stable_partition(row.second.begin(), row.second.end(),
				[predicate, date](std::string event) {
				return !predicate(date, event);
				});
			if (it != row.second.end()) size_to_del = row.second.end() - it;
			/*row.second.erase(row.second.begin(), it);
			if (row.second.empty()) {
				db_for_last_.erase(row.first);
			}*/
			for (size_t i = 0; i < size_to_del; i++) {
				if (!row.second.empty()) {
					d_e_.erase({date, row.second.back()});
					row.second.pop_back();
					count++;
				}
				else {
					db_for_last_.erase(date);
				}
			}
		}
		return count;
	}

	template<typename Func>
	std::vector<DbRow> FindIf(Func& predicate) const {
		std::vector<DbRow> found;
		for (const auto& row : db_for_last_) {
			for (const auto& event : row.second) {
				if (predicate(row.first, event)) found.push_back({ row.first, event });
			}
		}
		return found;
	}
	DbRow Last(const Date& date) const;
private:
	Db db_;
	std::map<Date, std::vector<std::string>> db_for_last_;
	std::set <DbRow> d_e_;
};