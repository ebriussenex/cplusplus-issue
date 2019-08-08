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

class SortedStrings {
public:
	void AddString(const std::string& s) {
		strs.push_back(s);
	}
	std::vector <std::string> GetSortedStrings() {
		sort(strs.begin(), strs.end());
		return strs;
	}
private:
	std::vector <std::string> strs;
};

class Name{
public:
	std::string fname;
	std::string lname;
};

class Person {
public:
	void ChangeFirstName(int year, const std::string& first_name) {
		if(names.count(year) == 0){
			names[year].fname = first_name;
			names[year].lname = "";
			years.insert(year);
		}
	}
	void ChangeLastName(int year, const std::string& last_name) {
		if(names.count(year) == 0){
			names[year].lname = last_name;
			names[year].fname = "";
			years.insert(year);
		}
	}
	std::string GetFullName(int year) {
		if(names.size() == 0){
			return "Incognito";
		}
		else{
			for(const auto& i : years){
				if(year < i)	return "Incognito";
				break;
			}
		}
		for(const auto& i : names){
			if(year >= i.first){
				if(i.second.fname != ""){
					cur_fname = i.second.fname;
				}
				if(i.second.lname != ""){
					cur_lname = i.second.lname;
				}
			}
		}
		if(cur_fname == "" || cur_lname == ""){
			if(cur_fname != ""){
				return cur_fname + " with unknown last name";
			}
			else if(cur_lname != ""){
				return cur_lname + " with unkown first name";
			}
			else{
				return "Incognito";
			}
		}
		else{
			return cur_fname + " " + cur_lname;
		}
	}
private:
	std::map <int, Name> names;
	std::set <int> years;
	std::string cur_fname = "";
	std::string cur_lname = "";
};

void PrintSortedStrings(SortedStrings& strings) {
	for (const std::string& s : strings.GetSortedStrings()) {
		std::cout << s << " ";
	}
	std::cout << std::endl;
}

int main() {
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		std::cout << person.GetFullName(year) << std::endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullName(year) << std::endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullName(year) << std::endl;
	}

	system("PAUSE");
	return 0;
}
