#include "database.h"



void Database::Add(const Date& date, const std::string& event)
{
	if (!d_e_[date].count(event)) {
		db_sort_[date].push_back(event);
		std::sort(db_sort_[date].begin(), db_sort_[date].end());
		db_last_[date].push_back(event);
		d_e_[date].insert(event);
	}
}

void Database::Print(std::ostream& os) const
{
	for (auto& item : db_sort_) {
		for (auto& jtem : item.second) {
			os << item.first << " " << jtem << std::endl;
		}
	}
}

DbRow Database::Last(const Date& date) const
{
	if (db_last_.empty()) throw std::invalid_argument("No entries");
	auto it = db_last_.upper_bound(date);
	if (it != db_last_.begin()) {
		auto itt = std::prev(it);
		if (!itt->second.empty()) {
			return{ itt->first, itt->second.back() };
		}
	}
	else throw std::invalid_argument("No entries");
}