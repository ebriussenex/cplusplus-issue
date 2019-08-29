#include "database.h"



void Database::Add(const Date& date, const std::string& event)
{
	db_[date].insert(event);
}

void Database::Print(std::ostream& os) const
{
	for (const auto& item : db_) {
		for (const auto& jtem : item.second) {
			os << item.first << " " << jtem << std::endl;
		}
	}
}

template <typename Func>
int Database::RemoveIf(Func& predicate) {
	auto it = db_.stable_partition(db_.begin(), db_.end(), predicate);
	int count = db_.count(db_.begin(), it);
	db_.erase(db_.begin(), db_.end());
	return count;
}

template<typename Func>
std::vector<Date, std::set<std::string>>  Database::FindIf(Func& predicate) {
	std::vector<Date, std::set<std::string>> found;
	for (const auto& item : db_) {
		if (predicate(item.first, item.second)) found.push_back(item);
	}
	return found;
}
