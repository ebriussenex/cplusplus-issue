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
	int RemoveIf(Func& predicate);
	template <typename Func>
	std::vector<DbRow> FindIf(Func& predicate) const;
	DbRow Last(const Date& date) const;
private:
	Db db_;
	DbLast db_for_last_;
	std::set <DbRow> d_e_;
};