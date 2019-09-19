#include "database.h"



void Database::Add(const Date& date, const std::string& event)
{
<<<<<<< Updated upstream
	if (!d_e_.count({ date, event })) {
		db_for_last_[date].push_back(event);
		d_e_.insert({ date, event });
=======
	if (!d_e_[date].count(event)) {
		db_last_[date].push_back(event);
		d_e_[date].insert(event);
>>>>>>> Stashed changes
	}
}

void Database::Print(std::ostream& os) const
{
<<<<<<< Updated upstream
	for (const auto& item : db_for_last_) {
=======
	for (const auto& item : db_last_) {
>>>>>>> Stashed changes
		for (const auto& jtem : item.second) {
			os << item.first << " " << jtem << std::endl;
		}
	}
}

DbRow Database::Last(const Date& date) const
{
<<<<<<< Updated upstream
	if (db_for_last_.empty()) throw std::invalid_argument("No entries");
	auto it = db_for_last_.upper_bound(date);
	if (it != db_for_last_.begin()) {
=======
	if (db_last_.empty()) throw std::invalid_argument("No entries");
	auto u_b = db_last_.upper_bound(date);
	if (u_b != db_last_.end()) {
		if (date < u_b->first) {
			if (u_b == db_last_.begin()) throw std::invalid_argument("No entries");
			else u_b = std::prev(u_b);
		}
	}
	else {
		if (u_b == db_last_.begin()) throw std::invalid_argument("No entries");
		u_b = std::prev(u_b);
	}
	return {u_b->first, *(prev(u_b->second.end()))};
	
	/*if (u_b == db_last_.begin()) throw std::invalid_argument("No entries");
	else return { std::prev(u_b)->first, std::prev(u_b)->second.back() };*/

	/*if (db_last_.empty()) throw std::invalid_argument("No entries");
	auto l_b = db_last_.lower_bound(date);
	if (l_b == db_last_.begin() && db_last_.begin()->first != date) {
		throw std::invalid_argument("No entries");
	}
	else if (l_b == db_last_.begin() && db_last_.begin()->first == date) {
		return { date, l_b->second.back() };
	}
	else if (l_b == db_last_.end()) {
		auto prev_it = std::prev(l_b);
		return { prev_it->first, prev_it->second.back() };
	}
	else if (l_b->first == date) {
		return { date, l_b->second.back() };
	}
	else {
		auto prev_it = std::prev(l_b);
		return { prev_it->first, prev_it->second.back() };
	}*/
	
	/*if (db_last_.empty()) throw std::invalid_argument("No entries");
	const auto l_b = db_last_.lower_bound(date);
	if (l_b == db_last_.begin() && l_b->first != date) {
		throw std::invalid_argument("No entries");
	}
	else if (l_b->first == date) {
		const auto last_event = std::prev(l_b->second.end());
		return { l_b->first, *last_event };
	}
	const auto last_row = std::prev(l_b);
	const auto last_event = std::prev(l_b->second.end());
	return { last_row->first, *last_event };*/
	
	
	/*	if (db_last_.empty()) throw std::invalid_argument("No entries");
	auto it = db_last_.upper_bound(date);
	if (it != db_last_.begin()) {
>>>>>>> Stashed changes
		auto itt = std::prev(it);
		if (!itt->second.empty()) {
			return{ itt->first, itt->second.back() };
		}
	}
<<<<<<< Updated upstream
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

=======
	else throw std::invalid_argument("No entries");*/
}
>>>>>>> Stashed changes
