#include "database.h"



void Database::Add(const Date& date, const std::string& event)
{
	if (!d_e_.count({ date, event })) {
		db_for_last_[date].push_back(event);
		d_e_.insert({ date, event });
	}
}

void Database::Print(std::ostream& os) const
{
	for (const auto& item : db_for_last_) {
		for (const auto& jtem : item.second) {
			os << item.first << " " << jtem << std::endl;
		}
	}
}

DbRow Database::Last(const Date& date) const
{
	if (db_for_last_.empty()) throw std::invalid_argument("No entries");
	auto it = db_for_last_.upper_bound(date);
	if (it != db_for_last_.begin()) {
		auto itt = std::prev(it);
		if (!itt->second.empty()) {
			return{ itt->first, itt->second.back() };
		}
	}
	else throw std::invalid_argument("No entries");
	/*if (it == db_for_last_.begin() && date != it->first) {
		throw std::invalid_argument("No entries");
	}
	if (it == db_for_last_.end()) it = std::prev(it);*/
	/*return { it->first, it->second.back() };*/
}

//template <typename Func>
//int Database::RemoveIf(Func& predicate) {
//	int count = 0;
//	for (const auto& row : db_for_last_) {//deletes events due to condition
//		Date& date = row.first;
//		auto it = row.second.stable_partition([predicate, date](std::string event) {
//			return predicate(date, event);
//			});
//		count += it - row.second.begin();
//		row.second.erase(row.second.begin(), it);
//		if (row.second.empty()) {
//			db_for_last_.erase(row.first);
//		}
//	}
//	return count;
//}

//template<typename Func>
//std::vector<DbRow> Database::FindIf(Func& predicate) const {
//	std::vector<DbRow> found;
//	for (const auto& row : db_for_last_) {
//		for (const auto& event : row.second) {
//			if (predicate(row.first, event)) found.push_back({ row.first, event });
//		}
//	}
//	return found;
//}

//template<typename Func>
//std::vector<DbRow> Database::FindIf(Func& predicate) const {
//	std::vector<DbRow> found;
//	for (const auto& row : db_for_last_) {
//		for (const auto& event : row.second) {
//			if (predicate(row.first, event)) found.push_back({ row.first, event });
//		}
//	}
//	return found;
//}
//
//template <typename Func>
//int Database::RemoveIf(Func predicate) {
//	unsigned int size_to_del = 0, count = 0;
//	for (auto& row : db_for_last_) {//deletes events due to condition
//		Date date = row.first;
//		auto it = stable_partition(row.second.begin(), row.second.end(),
//			[predicate, date](std::string event) {
//				return !predicate(date, event);
//			});
//		if (it != row.second.end()) size_to_del = row.second.end() - it;
//		/*row.second.erase(row.second.begin(), it);
//		if (row.second.empty()) {
//			db_for_last_.erase(row.first);
//		}*/
//		for (size_t i = 0; i < size_to_del; i++) {
//			if (!row.second.empty()) {
//				d_e_.erase({ date, row.second.back() });
//				row.second.pop_back();
//				count++;
//			}
//			else {
//				db_for_last_.erase(date);
//			}
//		}
//	}
//	return count;
//}
//

