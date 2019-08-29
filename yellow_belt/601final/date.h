#pragma once
#include <iostream>
#include <istream>
#include <ostream>
//���������� ����������
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

//��������s

std::ostream& operator<<(std::ostream& stream, const Date& date);

bool operator<(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

//������� ParseDate

Date ParseDate(std::istream& is);