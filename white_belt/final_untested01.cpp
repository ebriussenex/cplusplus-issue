#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>
#include <exception>

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

#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <functional>

class Date {
public:
	Date() {
		year_ = 0;
		month_ = 0;
		day_ = 0;
	}
	Date(int year, int month, int day) {
		year_ = year;
		month_ = month;
		day_ = day;
	}
	int GetDay() const {
		return day_;
	}
	int GetMonth() const {
		return month_;
	}
	int GetYear() const {
		return year_;
	}
private:
	int year_, month_, day_;
};

std::ostream& operator<<(std::ostream& stream, const Date& date) {
	stream << std::setfill('0');
	stream << std::setw(4) << date.GetYear() << '-'
		<< std::setw(2) << date.GetMonth() << '-'
		<< std::setw(2) << date.GetDay();
	return stream;
}

class DataBase {
public:
	DataBase() {};
	void AddEvent(const Date& date, const std::string& event) {
		db_[date].push_back(event);
	}
	bool DeleteEvent(const Date& date, const std::string& event) {
		if (db_.count(date) > 0) {
			auto it = std::find(db_[date].begin(), db_[date].end(), event);
			if (it != db_[date].end()) {
				db_[date].erase(it);
				return true;
			}
		}
		return false;
	}
	int DeleteDate(const Date& date) {
		int count = 0;
		if (db_.count(date) > 0) {
			count = db_[date].size();
			db_.erase(date);
		}
		return count;
	}
	void Print() const {
		for (const auto& item : db_) {
			std::vector<std::string> copied = item.second;
			std::sort(copied.begin(), copied.end());
			for (const auto& jtem : copied) {
				std::cout << item.first << " " << jtem << std::endl;
			}
		}
	}
	void FindDate(const Date& date) {
		if (db_.count(date)) {
			for (size_t i = 0; i < db_[date].size(); i++) {
				std::sort(db_[date].begin(), db_[date].end());
				std::cout << db_[date][i] << std::endl;
			}
		}
	}
private:
	std::map <Date, std::vector <std::string>> db_;
};

std::istream& operator>>(std::istream& stream, Date& date) {
	int year, month, day;
	if (stream >> year && stream.ignore(1) && stream >> month && stream.ignore(1) && stream >> day) {
		date = Date(year, month, day);
	}
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

int main() {
	try {
		std::string command, line = "";
		DataBase db;
		while (std::cin >> command) {
			if (command != "Add" && command != "Del" && command != "Find" && command != "Print") {
				throw std::invalid_argument("Unknown command: " + command);
			}
			Date date;
			if (std::cin.peek() == ' ') {
				std::cin.ignore(1);
				int year = 0, month = 0, day = 0;
				//std::getline(std::cin, line);
				std::cin >> line;
				std::stringstream ss(line);
				ss >> year;
				if (!ss || ss.peek() != '-') {
					throw std::invalid_argument("Wrong date format: " + line);
				}
				ss.ignore(1);
				ss >> month;
				if (!ss || ss.peek() != '-') {
					throw std::invalid_argument("Wrong date format: " + line);
				}
				ss.ignore(1);
				ss >> day;
				if (!ss || ss.peek() != EOF) {
					throw std::invalid_argument("Wrong date format: " + line);
				}
				if (month > 12 || month < 1) {
					throw std::invalid_argument("Month value is invalid: " + std::to_string(month));
				}
				else if (day > 31 || day < 1) {
					throw std::invalid_argument("Day value is invalid: " + std::to_string(day));
				}
				if (command == "Add") {
					std::cin.ignore(1);
					std::cin >> line;
					db.AddEvent(Date(year, month, day), line);
				}
				if (command == "Del") {
					if (std::cin.peek() == ' ') {
						std::cin.ignore(1);
						std::cin >> line;
						bool f_event = db.DeleteEvent(Date(year, month, day), line);
						if (f_event)	std::cout << "Deleted successfully\n";
						else    std::cout << "Event not found\n";
					}
					else {
						int count_events_deleted = db.DeleteDate(Date(year, month, day));
						std::cout << "Deleted " + std::to_string(count_events_deleted) + " events\n";
					}
				}
				if (command == "Find") {
					db.FindDate(Date(year, month, day));
				}
			}
			if (command == "Print") {
				db.Print();
			}
			//print
		}
	}
	catch (std::invalid_argument& ex) {
		std::cout << ex.what();
	}
	return 0;
}