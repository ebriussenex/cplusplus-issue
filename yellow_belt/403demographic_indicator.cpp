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

enum class Gender {
	FEMALE,
	MALE
};

struct Person {
	int age;
	Gender gender;
	bool is_employed;
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
	if (range_begin == range_end) {
		return 0;
	}
	vector<typename InputIt::value_type> range_copy(range_begin, range_end);
	auto middle = begin(range_copy) + range_copy.size() / 2;
	nth_element(
		begin(range_copy), middle, end(range_copy),
		[](const Person& lhs, const Person& rhs) {
			return lhs.age < rhs.age;
		}
	);
	return middle->age;
}

void PrintStats(std::vector<Person> persons) {
	std::cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << std::endl;

	auto it = std::partition(persons.begin(), persons.end(), [](const Person& p) {
		return p.gender == Gender::FEMALE; });
	std::cout << "Median age for females = " << ComputeMedianAge(persons.begin(), it) << std::endl;
	std::cout << "Median age for males = " << ComputeMedianAge(it, persons.end()) << std::endl;

	it = std::partition(persons.begin(), persons.end(), [](const Person& p) {
		return (p.gender == Gender::FEMALE)&&(p.is_employed == true); });
	std::cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), it) << std::endl;

	it = std::partition(persons.begin(), persons.end(), [](const Person& p) {
		return (p.gender == Gender::FEMALE) && (p.is_employed == false); });
	std::cout << "Median age for unemployed females = " << ComputeMedianAge(persons.begin(), it) << std::endl;

	it = std::partition(persons.begin(), persons.end(), [](const Person& p) {
		return (p.gender == Gender::MALE) && (p.is_employed == true); });
	std::cout << "Median age for employed males = " << ComputeMedianAge(persons.begin(), it) << std::endl;

	it = std::partition(persons.begin(), persons.end(), [](const Person& p) {
		return (p.gender == Gender::MALE) && (p.is_employed == false); });
	std::cout << "Median age for unemployed males = " << ComputeMedianAge(persons.begin(), it) << std::endl;
}

int main() {
	std::vector<Person> persons = {
	 {31, Gender::MALE, false},
	 {40, Gender::FEMALE, true},
	 {24, Gender::MALE, true},
	 {20, Gender::FEMALE, true},
	 {80, Gender::FEMALE, false},
	 {78, Gender::MALE, false},
	 {10, Gender::FEMALE, false},
	 {55, Gender::MALE, true},
	};
	PrintStats(persons);
	return 0;
	return 0;
}
