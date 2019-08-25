#include <iostream>
#include <iomanip>

#include "date.h"

//объ€вление интерфейса класса
Date::Date(int year = 0, int month = 0, int day = 0) :
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

//функци€ parseDate

Date ParseDate(std::istream& is)
{
	return 0;
}
