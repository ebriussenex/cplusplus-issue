#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>
#include <iostream>
#include <stack>
#include <queue>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <fstream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <list>
#include <cstring>

std::string FindNameByYear(const std::map<int, std::string>& names, int year) {
	std::string name;
	for (const auto& item : names) {
		if (item.first <= year)	name = item.second;
		else break;
	}
	return name;
}

class Name {
public:
	std::string fname;
	std::string lname;
};

class Person {
public:
	void ChangeFirstName(int year, const std::string& first_name) {
		if (names.count(year) == 0) {
			names[year].lname = "";
		}
		names[year].fname = first_name;
	}
	void ChangeLastName(int year, const std::string& last_name) {
		if (names.count(year) == 0) {
			names[year].fname = "";
		}
		names[year].lname = last_name;
	}
	std::string GetFullName(int year) {
		const std::string first_name = FindNameByYear(first_names, year);
		const std::string last_name = FindNameByYear(last_names, year);
		if (first_name.empty() && last_name.empty())	return "Incognito";
		else if (first_name.empty())	return last_name + " with unknown first name";
		else if (last_name.empty())		return first_name + " with unknown last name";
		else	return first_name + " " + last_name;
	}
	std::string GetFullNameWithHistory(int year) {
		std::string cur_fname = "", cur_lname = "";
		std::vector<std::string> prev_lnames, prev_fnames;
		if (!names.size())	return "Incognito";
		else {
			for (const auto& i : names) {
				if (year < i.first) return "Incognito";
				break;
			}
		}
		for (const auto& i : names) {
			if (year >= i.first) {
				if (i.second.fname != "") {
					if (i.second.fname != cur_fname && cur_fname != "") {
						prev_fnames.push_back(cur_fname);
					}
					cur_fname = i.second.fname;
				}
				if (i.second.lname != "") {
					if (i.second.lname != cur_lname && cur_lname != "") {
						prev_lnames.push_back(cur_lname);
					}
					cur_lname = i.second.lname;
				}
			}
		}
		if (prev_fnames.size()) {
			cur_fname += " (" + prev_fnames[prev_fnames.size() - 1];
			if (prev_fnames.size() > 1) {
				for (auto i = prev_fnames.size() - 1; i > 0; i--) {
					cur_fname += ", " + prev_fnames[i - 1];
				}
			}
			cur_fname += ")";
		}
		if (prev_lnames.size()) {
			cur_lname += " (" + prev_lnames[prev_lnames.size() - 1];
			if (prev_lnames.size() > 1) {
				for (auto i = prev_lnames.size() - 1; i > 0; i--) {
					cur_lname += ", " + prev_lnames[i - 1];
				}
			}
			cur_lname += ")";
		}
		if (cur_fname == "")	return cur_lname + " with unknown first name";
		else if (cur_lname == "")	return cur_fname + " with unknown last name";
		else return cur_fname + " " + cur_lname;
	}
private:
	std::map<int, std::string> first_names;
	std::map<int, std::string> last_names;
	std::map <int, Name> names;
};

int main() {
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeFirstName(1990, "Polina");
	person.ChangeLastName(1990, "Volkova-Sergeeva");
	std::cout << person.GetFullNameWithHistory(1990) << std::endl;

	person.ChangeFirstName(1966, "Pauline");
	std::cout << person.GetFullNameWithHistory(1966) << std::endl;

	person.ChangeLastName(1960, "Sergeeva");
	for (int year : {1960, 1967}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeLastName(1961, "Ivanova");
	std::cout << person.GetFullNameWithHistory(1967) << std::endl;

	return 0;
}