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

class Person {
public:
	void ChangeFirstName(int year, const std::string& first_name) {
		fnames[year] = first_name;
	}
	void ChangeLastName(int year, const std::string& last_name) {
		lnames[year] = last_name;
	}
	std::string GetFullName(int year) {
		auto pf = std::find_if(fnames.begin(), fnames.end(), [year](auto x) { return year >= x.first; });
		auto pl = std::find_if(lnames.begin(), lnames.end(), [year](auto x) { return year >= x.first; });
		auto lln = lnames.end();
		auto lfn = fnames.end();
		if (pf == fnames.end() && pl == lnames.end()) {
			return "Incognito";
			/*std::cout << "Incognito\n";*/
		}
		else if (pf != fnames.end() && pl == lnames.end()) {
			return pf->second + " with unknown last name";
			/*std::cout << pf->second << " with unknown last name\n";*/
		}
		else if (pl != lnames.end() && pf == fnames.end()) {
			/*std::cout << pl->second << " with unkown first name\n";*/
			return pl->second + " with unkown first name";
		}
		else {
			/*std::cout << pf->second << " " << pl->second << std::endl;*/
			return pf->second + " " + pl->second;
		}
	}
private:
	std::map <int, std::string> fnames;
	std::map <int, std::string> lnames;
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