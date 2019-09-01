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
	std::map<Date, std::vector<std::string>> to_print_;
	Database() {};
	void Add(const Date& date, const std::string& event);
	void Print(std::ostream& os) const;

	template <typename Func>
	int RemoveIf(Func predicate) {
		unsigned int size_to_del = 0, count = 0;
		std::vector <Date> clean;
		for (auto& row : db_sort_) {//deletes events due to condition
			size_to_del = 0;
			auto date = row.first;
			auto it = stable_partition(row.second.begin(), row.second.end(), [predicate, date](std::string event) {return !predicate(date, event); });
			if (it != row.second.end()) size_to_del = row.second.end() - it;
			if (it == row.second.begin()) {
				clean.push_back(date);
				count += row.second.size();
			}
			else {
				for (size_t i = 0; i < size_to_del; ++i) {
					if (!row.second.empty()) {
						d_e_.erase(date);
						db_last_[date].erase(std::remove(db_last_[date].begin(), db_last_[date].end(), row.second.back()), db_last_[date].end());
						if (db_last_[date].empty()) db_last_.erase(date);
						row.second.pop_back();
						count++;
					}
					else clean.push_back(date);
				}
			}
		}
		for (const auto& date : clean) {
			d_e_.erase(date);
			db_sort_.erase(date);
			db_last_.erase(date);
		}
		/*PrintDbLast();*/
		return count;
	}

	template<typename Func>
	std::set<DbRow> FindIf(Func predicate) const {
		std::set<DbRow> found;
		for (auto& row : db_sort_) {
			for (const auto& event : row.second) {
				if (predicate(row.first, event)) found.insert({ row.first, event });
			}
		}
		return found;
	}

	void PrintDbLast() {
		for (const auto& item : db_last_) {
			for (const auto& jtem : item.second) {
				std::cout << "L: " << item.first << " " << jtem << std::endl;
			}
		}
	}

	DbRow Last(const Date& date) const;
private:
	Db db_;
	std::map<Date, std::vector<std::string>> db_sort_;
	std::map<Date, std::vector<std::string>> db_last_;
	std::map <Date, std::set<std::string>> d_e_;
};