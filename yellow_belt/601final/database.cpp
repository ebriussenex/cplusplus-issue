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
	if (db_.empty()) throw std::invalid_argument("No entries");
	auto it = db_for_last_.lower_bound(date);
	if (it == db_for_last_.begin() && date < it->first) {
		throw std::invalid_argument("No entries");
	}
	if (it == db_for_last_.end()) it = std::prev(it);
	return { it->first, it->second.back() };
}

template <typename Func>
int Database::RemoveIf(Func& predicate) {
	int count = 0;
	for (const auto& row : db_for_last_) {//deletes events due to condition
		Date& date = row.first;
		auto it = row.second.stable_partition([predicate, date](std::string event) {
			return predicate(date, event);
			});
		count += it - row.second.begin();
		row.second.erase(row.second.begin(), it);
		if (row.second.empty()) {
			db_for_last_.erase(row.first);
		}
	}
	return count;
}

template<typename Func>
std::vector<DbRow> Database::FindIf(Func& predicate) const {
	std::vector<DbRow> found;
	for (const auto& row : db_for_last_) {
		for (const auto& event : row.second) {
			if (predicate(row.first, event)) found.push_back({ row.first, event });
		}
	}
	return found;
}


