#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>

#include "date.h"

class Database {
public:
	Database() {};
	void Add(const Date& date, const std::string& event);
	void Print(std::ostream& os) const;
	template <typename Func>
	int RemoveIf(Func& predicate);
	template <typename Func>
	std::vector<Date, std::set<std::string>> FindIf(Func& predicate);
private:
	std::map <Date, std::set <std::string>> db_;
};