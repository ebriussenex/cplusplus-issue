#include <iostream>
#include <iomanip>

#include "date.h"

using namespace std;
//объ€вление интерфейса класса
Date::Date() : year_(1), month_(1), day_(1) {}

Date::Date(const int year, const int month, const int day) :
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
	return !(lhs == rhs);
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

std::ostream& operator<<(std::ostream& stream, const DbRow& dbrow)
{
	stream << dbrow.GetDate() << " " << dbrow.GetEvent();
	return stream;
}

DbRow::DbRow(const Date& date, const std::string& event) : 
	date_(date), event_(event) {}

std::string DbRow::GetEvent() const
{
	return event_;
}

Date DbRow::GetDate() const
{
	return date_;
}

bool operator<(const DbRow& lhs, const DbRow& rhs) {
	if (lhs.GetDate() == rhs.GetDate()) {
		return lhs.GetEvent() < rhs.GetEvent();
	}
	return lhs.GetDate() < rhs.GetDate();
}