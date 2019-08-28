#pragma once
#include <iostream>
#include <istream>
#include <ostream>
//���������� ����������
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

//��������s

std::ostream& operator<<(std::ostream& stream, const Date& date);

bool operator<(Date& lhs, Date& rhs);
bool operator==(Date& lhs, Date& rhs);

//������� ParseDate

Date ParseDate(std::istream& is);