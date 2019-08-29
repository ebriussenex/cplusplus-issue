#pragma once
#include <iostream>
#include <istream>
#include <ostream>
//объявление интерфейса
class Date {
public:
	Date(const int year, const int month, const int day);
	int GetMonth() const;
	int GetYear() const;
	int GetDay() const;
private:
	const int year_;
	const int month_;
	const int day_;
};

//операторs

std::ostream& operator<<(std::ostream& stream, const Date& date);

bool operator<(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

//функция ParseDate

Date ParseDate(std::istream& is);