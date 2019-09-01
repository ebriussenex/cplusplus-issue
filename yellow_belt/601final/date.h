#pragma once
#include <iostream>
#include <istream>
#include <ostream>
#include <memory>
//объявление интерфейса

using namespace std;

class Date {
public:
	Date();
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

//dbRow

class DbRow {
public:
	DbRow() {}
	DbRow(const Date& date, const std::string& event);
	std::string GetEvent() const;
	Date GetDate() const;
private:
	const Date date_;
	const std::string event_;
};

std::ostream& operator<<(std::ostream& stream, const DbRow& dbrow);

bool operator<(const DbRow& lhs, const DbRow& rhs);