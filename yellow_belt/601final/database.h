#pragma once
#include <map>
#include <set>
#include <string>

#include "date.h"

class Database {
public:
	Database() {};
	void Add(const Date& date, const std::string& event);
	void Print(std::ostream& os) const;
	template <typename Func>
	int RemoveIf(Func& predicate);

private:
	std::map <Date, std::set <std::string>> db_;
};