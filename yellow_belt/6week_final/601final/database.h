#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>
#include <stdexcept>
#include <exception>
#include <algorithm>
#include <functional>
#include <iostream>
#include <iomanip>

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
<<<<<<< Updated upstream
		unsigned int size_to_del = 0, count = 0;
		std::vector <Date> clean;
		for (auto& row : db_for_last_) {//deletes events due to condition
			Date date = row.first;
			auto it = stable_partition(row.second.begin(), row.second.end(),
				[predicate, date](std::string event) {
					return !predicate(date, event);
				});
			size_to_del = row.second.end() - it;
			if (it == row.second.begin()) {
				clean.push_back(date);
				count += row.second.size();
			}
			else {
				for (size_t i = 0; i < size_to_del; ++i) {
					if (!row.second.empty()) {
						d_e_.erase({ date, row.second.back() });
						row.second.pop_back();
						count++;
					}
					else {
						clean.push_back(date);
					}
				}
			}
		}
		for (const auto& date : clean) {
			db_for_last_.erase(date);
=======
		unsigned int count = 0;
		std::map<Date, std::vector<std::string>::iterator> to_delete;
		for (auto& row : db_last_) {
			auto& date = row.first;
			auto it = stable_partition(row.second.begin(), row.second.end(), [predicate, date](std::string event) {return !predicate(date, event); });
			to_delete[date] = it;
		}
		for (auto /*(date, iter)*/ smth : to_delete) {
			count += db_last_[smth.first].end() - smth.second;
			db_last_[smth.first].erase(smth.second, db_last_[smth.first].end());
			d_e_[smth.first] = std::set<std::string>(db_last_[smth.first].begin(), db_last_[smth.first].end());
			if (db_last_[smth.first].empty()) {
				db_last_.erase(smth.first);
				d_e_.erase(smth.first);
			}
>>>>>>> Stashed changes
		}
		return count;
		//unsigned int count = 0;
		//std::vector <Date> clean;
		//for (auto i = db_last_.begin(); i != db_last_.end(); i++) {
		//	auto date = i->first;
		//	auto it = std::stable_partition(i->second.begin(), i->second.end(), [predicate, date](std::string event) {return !predicate(date, event); });
		//	count += i->second.end() - it;
		//	d_e_[i->first].clear();
		//	d_e_[i->first].insert(i->second.begin(), it);
		//	i->second.erase(it, i->second.end());
		//	if (/*i->second.begin() == i->second.end()*/i->second.empty()) clean.push_back(i->first);
		//}
		//for (auto& item : clean) {
		//	db_last_.erase(item);
		//	d_e_.erase(item);
		//}
		//return count;

		//unsigned int size_to_del = 0, count = 0;
		//std::vector <Date> clean;
		//for (auto& row : db_sort_) {//deletes events due to condition
		//	size_to_del = 0;
		//	auto date = row.first;
		//	auto it = stable_partition(row.second.begin(), row.second.end(), [predicate, date](std::string event) {return !predicate(date, event); });
		//	if (it != row.second.end()) size_to_del = row.second.end() - it;
		//	if (it == row.second.begin()) {
		//		clean.push_back(date);
		//		count += row.second.size();
		//	}
		//	else {
		//		for (size_t i = 0; i < size_to_del; ++i) {
		//			if (!row.second.empty()) {
		//				d_e_.erase(date);
		//				db_last_[date].erase(std::remove(db_last_[date].begin(), db_last_[date].end(), row.second.back()), db_last_[date].end());
		//				if (db_last_[date].empty()) db_last_.erase(date);
		//				row.second.pop_back();
		//				count++;
		//			}
		//			else clean.push_back(date);
		//		}
		//	}
		//}
		//for (const auto& date : clean) {
		//	d_e_.erase(date);
		//	db_last_.erase(date);
		//}
		///*PrintDbLast();*/
		//return count;
	}

<<<<<<< Updated upstream
	template<typename Func>
	std::vector<DbRow> FindIf(Func predicate) const {
		std::vector<DbRow> found;
		for (const auto& row : db_for_last_) {
=======
	/*template<typename Func>
	std::set<DbRow> FindIf(Func predicate) const {
		std::set<DbRow> found;
		for (auto& row : db_last_) {
>>>>>>> Stashed changes
			for (const auto& event : row.second) {
				if (predicate(row.first, event)) found.push_back({ row.first, event });
			}
		}
		return found;
<<<<<<< Updated upstream
	}
	DbRow Last(const Date& date) const;
private:
	Db db_;
	std::map<Date, std::vector<std::string>> db_for_last_;
	std::set <DbRow> d_e_;
=======
	}*/

	template<typename Func>
	vector<pair<Date, string>> FindIf(Func predicate) const {
		vector<pair<Date, string>> found;
		for (const auto& item : db_last_) {
			auto& date = item.first;
			auto& events = item.second;
			auto l = [&predicate, &date](const string& event) {return predicate(date, event); };
			for (auto it = find_if(events.begin(), events.end(), l);
				it != item.second.end();
				it = find_if(next(it), item.second.end(), l)) {
				found.push_back(make_pair(date, *it));
			}
		}
		return found;
	}
	DbRow Last(const Date& date) const;
private:
	std::map<Date, std::vector<std::string>> db_last_;
	std::map <Date, std::set<std::string>> d_e_;
>>>>>>> Stashed changes
};