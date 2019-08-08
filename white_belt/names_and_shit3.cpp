#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>

#include <ios>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <fstream>

#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <utility>
#include <list>
#include <forward_list>
#include <bitset>

#include <iomanip>
#include <algorithm>
#include <string>
#include <regex>
#include <iterator>

#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

#include <chrono>

std::string FindNameByYear(const std::map<int, std::string>& names, int year) {
	std::string name;
	for (const auto& item : names) {
		if (item.first <= year)	name = item.second;
		else break;
	}
	return name;
}

std::string FindHistoryByYear(const std::map<int, std::string>& names, int year) {
	std::string name = "";
	std::string add;
	size_t it;
	std::vector <std::string> history;
	for (const auto& i : names) {
		if (i.first <= year) {
			if (name != "") {
				if (history.size() != 0) {
					if (name != history[history.size() - 1]) {
						history.push_back(name);
					}
				}
				else {
					history.push_back(name);
				}
			}
			name = i.second;
		}
		else break;
	}
	if (history.empty()) {
		return name;
	}
	else if (history[history.size() - 1] == name) {
		it = history.size() - 2;
		if (it == -1) {
			return name;
		}
	}
	else {
		it = history.size() - 1;
	}
	name += " (" + history[it];
	for (size_t i = it; i > 0; i--) {
		name += ", " + history[i - 1];
	}
	name += ")";
	return name;
}

class Name {
public:
	std::string fname;
	std::string lname;
};

class Person {
public:
	Person(const std::string& first_name, const std::string& last_name, int year) {
		first_names[year] = first_name;
		last_names[year] = last_name;
		birth_date = year;
	}
	void ChangeFirstName(int year, const std::string& first_name) {
		if (year >= birth_date) {
			first_names[year] = first_name;
		}
	}
	void ChangeLastName(int year, const std::string& last_name) {
		if (year >= birth_date) {
			last_names[year] = last_name;
		}
	}
	std::string GetFullName(int year) const {
		if (year >= birth_date) {
			const std::string first_name = FindNameByYear(first_names, year);
			const std::string last_name = FindNameByYear(last_names, year);
			if (first_name.empty() && last_name.empty())	return "Incognito";
			else if (first_name.empty())	return last_name + " with unknown first name";
			else if (last_name.empty())		return first_name + " with unknown last name";
			else	return first_name + " " + last_name;
		}
		else return "No person";
	}
	std::string GetFullNameWithHistory (int year) const {
		if (year >= birth_date) {
			const std::string first_name = FindHistoryByYear(first_names, year);
			const std::string last_name = FindHistoryByYear(last_names, year);
			if (first_name.empty() && last_name.empty())	return "Incognito";
			else if (first_name.empty())	return last_name + " with unknown first name";
			else if (last_name.empty())		return first_name + " with unknown last name";
			else	return first_name + " " + last_name;
		}
		else return "No person";
	}
private:
	std::map<int, std::string> first_names;
	std::map<int, std::string> last_names;
	int birth_date;
};

class ReversibleString {
public:
	ReversibleString() {
		str_ = "";
	}
	ReversibleString(const std::string& str) {
		str_ = str;
	}
	void Reverse() {
		reverse(str_.begin(), str_.end());
	}
	std::string ToString() const{
		return str_;
	}
private:
	std::string str_;
};

int main() {
	Person person("Polina", "Sergeeva", 1960);
	for (int year : {1959, 1960}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeFirstName(1965, "Appolinaria");
	person.ChangeLastName(1967, "Ivanova");
	for (int year : {1965, 1967}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	return 0;
}