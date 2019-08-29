#include <iostream>
#include <iomanip>

#include "date.h"

//объ€вление интерфейса класса
Date::Date(const int year = 0, const int month = 0, const int day = 0) :
	year_(year), month_(month), day_(day) {}

int Date::GetMonth() const
{
	return month_;
}

int Date::GetYear() const
{
	return year_;
}

int Date::GetDay() const
{
	return day_;
}
//оператор вывода дл€ Date

std::ostream& operator<<(std::ostream& stream, const Date& date) {
	stream << std::setfill('0');
	stream << std::setw(4) << date.GetYear() << '-'
		<< std::setw(2) << date.GetMonth() << '-'
		<< std::setw(2) << date.GetDay();
	return stream;
}

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.GetDay() < rhs.GetDay();
		}
		return lhs.GetMonth() < rhs.GetMonth();
	}
	return lhs.GetYear() < rhs.GetYear();
}

bool operator<=(const Date& lhs, const Date& rhs)
{
	return lhs < rhs || lhs == rhs;
}

bool operator==(const Date& lhs, const Date& rhs) {
	return (lhs.GetDay() == rhs.GetDay() &&
		lhs.GetMonth() == rhs.GetMonth() &&
		lhs.GetYear() == rhs.GetYear());
}

bool operator>(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.GetDay() > rhs.GetDay();
		}
		return lhs.GetMonth() > rhs.GetMonth();
	}
	return lhs.GetYear() > rhs.GetYear();
}

bool operator>=(const Date& lhs, const Date& rhs)
{
	return lhs > rhs || lhs == rhs;
}

bool operator!=(const Date& lhs, const Date& rhs)
{
	return lhs != rhs;
}

//функци€ parseDate

Date ParseDate(std::istream& is)
{
	int year = 0, month = 0, day = 0;
	if (is >> year && is.ignore(1) && is >> month && is.ignore(1) && is >> day) {
		return { year, month, day };
	}
	return { year, month, day };
}
