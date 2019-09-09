#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <cstdint>
#include <memory>

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

#include "test_runner.h"
#include "airline_ticket.h"

std::ostream & operator<<(std::ostream & os, const Date & date) {
	os << date.year << "-" << date.month << "-" << date.day << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, const Time& time) {
	os << time.hours << ":" << time.minutes << std::endl;
	return os;
}

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.year == rhs.year) {
		if (lhs.month == rhs.month)
			return lhs.day < rhs.day;
		return lhs.month < rhs.month;
	}
	return lhs.year < rhs.year;
}

bool operator==(const Date& lhs, const Date& rhs) {
	return (lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day);
}

bool operator<(const Time& lhs, const Time& rhs) {
	if (lhs.hours == rhs.hours)
		return lhs.minutes < rhs.minutes;
	return lhs.hours < rhs.hours;
}

bool operator==(const Time& lhs, const Time& rhs) {
	return lhs.hours == rhs.hours && lhs.minutes == rhs.minutes;
}

bool operator!=(const Date& lhs, const Date& rhs) {
	return !(lhs == rhs);
}

bool operator!=(const Time& lhs, const Time& rhs) {
	return !(lhs == rhs);
}

std::istream& operator>>(std::istream& is, Date& date) {
	is >> date.year;
	is.ignore(1);
	is >> date.month;
	is.ignore(1);
	is >> date.day;
	return is;
}

std::istream& operator>>(std::istream& is, Time& time) {
	is >> time.hours;
	is.ignore(1);
	is >> time.minutes;
	return is;
}

#define SORT_BY(field)                                 \
[](const AirlineTicket& lhs, const AirlineTicket& rhs){\
	return lhs.field < rhs.field;                      \
}

void TestSortBy() {
	std::vector<AirlineTicket> tixs = { 
	{ "VKO", "AER", "Utair",{ 2018, 2, 28 }, { 17, 40 }, { 2018, 2, 28 }, { 20, 0 }, 1200 },
	{"AER", "VKO", "Utair", { 2018, 3, 5 }, { 14, 15 }, { 2018, 3, 5 }, { 16, 30 }, 1700 },
	{ "AER", "SVO", "Aeroflot",{ 2018, 3, 5 }, { 18, 30 }, { 2018, 3, 5 }, { 20, 30 }, 2300 },
	{"PMI", "DME", "Iberia", { 2018, 2, 8 }, { 23, 00 }, { 2018, 2, 9 },{ 3, 30 }, 9000 },
	{ "CDG", "SVO", "AirFrance", { 2018, 3, 1 }, { 13, 00 }, { 2018, 3, 1 }, { 17, 30 }, 8000 }, };

	std::sort(tixs.begin(), tixs.end(), SORT_BY(price));
	ASSERT_EQUAL(tixs.front().price, 1200);
	ASSERT_EQUAL(tixs.back().price, 9000);

	std::sort(tixs.begin(), tixs.end(), SORT_BY(from));
	ASSERT_EQUAL(tixs.front().from, "AER");
	ASSERT_EQUAL(tixs.back().from, "VKO");

	std::sort(tixs.begin(), tixs.end(), SORT_BY(arrival_date));
	ASSERT_EQUAL(tixs.front().arrival_date, (Date{ 2018, 2, 9 }));
	ASSERT_EQUAL(tixs.back().arrival_date, (Date{ 2018, 3, 5 }));
}

#define UPDATE_FIELD(ticket, field, values){ \
	auto it = values.find(#field);           \
	if (it != values.end()) {                \
		std::istringstream is(it->second);   \
		is >> ticket.field;                  \
	}                                        \
}

void TestUpdate() {
	AirlineTicket t;
	t.price = 0;

	const std::map<std::string, std::string> updates1 = {
	  {"departure_date", "2018-2-28"},
	  {"departure_time", "17:40"},
	};
	UPDATE_FIELD(t, departure_date, updates1);
	UPDATE_FIELD(t, departure_time, updates1);
	UPDATE_FIELD(t, price, updates1);

	ASSERT_EQUAL(t.departure_date, (Date{ 2018, 2, 28 }));
	ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
	ASSERT_EQUAL(t.price, 0);

	const std::map<std::string, std::string> updates2 = {
	  {"price", "12550"},
	  {"arrival_time", "20:33"},
	};
	UPDATE_FIELD(t, departure_date, updates2);
	UPDATE_FIELD(t, departure_time, updates2);
	UPDATE_FIELD(t, arrival_time, updates2);
	UPDATE_FIELD(t, price, updates2);
	ASSERT_EQUAL(t.departure_date, (Date{ 2018, 2, 28 }));
	ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
	ASSERT_EQUAL(t.price, 12550);
	ASSERT_EQUAL(t.arrival_time, (Time{ 20, 33 }));
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestUpdate);
}

