#pragma once

#include <string>

struct Date {
	int year, month, day;
};

struct Time {
	int hours, minutes;
};

struct AirlineTicket {
	std::string from;
	std::string to;
	std::string airline;
	Date departure_date;
	Time departure_time;
	Date arrival_date;
	Time arrival_time;
	int price;
};

std::ostream& operator<<(std::ostream& os, const Date& date);
std::ostream& operator<<(std::ostream& os, const Time& time);
std::istream& operator>>(std::istream& is, const Date& date);
std::istream& operator>>(std::istream& is, const Time& time);

bool operator<(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator<(const Time& lhs, const Time& rhs);
bool operator==(const Time& lhs, const Time& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator!=(const Time& lhs, const Time& rhs);
