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
	void ChangeFirstName(int year, const std::string& first_name) {
		first_names[year] = first_name;
	}
	void ChangeLastName(int year, const std::string& last_name) {
		last_names[year] = last_name;
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
		const std::string first_name = FindHistoryByYear(first_names, year);
		const std::string last_name = FindHistoryByYear(last_names, year);
		if (first_name.empty() && last_name.empty())	return "Incognito";
		else if (first_name.empty())	return last_name + " with unknown first name";
		else if (last_name.empty())		return first_name + " with unknown last name";
		else	return first_name + " " + last_name;
	}
private:
	std::map<int, std::string> first_names;
	std::map<int, std::string> last_names;
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