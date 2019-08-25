#pragma once
#include <iostream>
#include <istream>
#include <ostream>
//объявление интерфейса
class Date {
public:
	Date(int year, int month, int day);
	int GetMonth() const;
	int GetYear() const;
	int GetDay() const;
private:
	const int year_;
	const int month_;
	const int day_;
};

//оператор вывода

std::ostream& operator<<(std::ostream& stream, const Date& date);

//функция ParseDate

Date ParseDate(std::istream& is);