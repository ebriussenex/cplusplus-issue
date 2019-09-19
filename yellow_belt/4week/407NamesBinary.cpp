#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <cstdint>

#include <ios>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cfenv>
#include <iomanip>

#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <tuple>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <utility>
#include <list>
#include <forward_list>
#include <bitset>
#include <algorithm>
#include <string>
#include <regex>
#include <iterator>
#include <numeric>

#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <functional>

//std::map<int, std::string>::const_iterator FindNearestElement(const std::map<int, std::string>& numbers, int border) {
//	auto r = numbers.lower_bound(border);
//	if (r == numbers.begin()) return r;
//	if (r == numbers.end()) return std::prev(numbers.end());
//	else {
//		if (border - std::prev(r)->first <= r->first - border) return std::prev(r);
//		else return r;
//	}
//}

std::string FindNameByYear(const std::map<int, std::string>& names, int year) {
	auto it = names.upper_bound(year);
	if (it == names.begin()) return "";
	return std::prev(it)->second;
	
}

class Person {
public:
	void ChangeFirstName(int year, const std::string& first_name) {
		first_names[year] = first_name;
	}
	void ChangeLastName(int year, const std::string& last_name) {
		last_names[year] = last_name;
	}
	std::string GetFullName(int year) {
		const std::string fname = FindNameByYear(first_names, year);
		const std::string lname = FindNameByYear(last_names, year);
		if (fname.empty() && lname.empty()) return "Incognito";
		if (!fname.empty()) {
			if (lname.empty()) return fname + " with unknown last name";
			else return fname + " " + lname;
		}
		else return lname + "with unknown first name";
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

	return 0;
}

