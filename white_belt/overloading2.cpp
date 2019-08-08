#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>

#include <ios>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cfenv>

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

#include <iomanip>
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

struct Duration {
	int hour;
	int minute;
	Duration(int h = 0, int m = 0) {
		int total = h * 60 + m;
		hour = total / 60;
		minute = total % 60;
	}
};

std::istream& operator>>(std::istream& stream, Duration& duration) {
	stream >> duration.hour;
	stream.ignore(1);
	stream >> duration.minute;
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Duration& duration) {
	stream << std::setfill('0');
	stream << std::setw(2) << duration.hour << ":"
		<< std::setw(2) << duration.minute;
	return stream;
}

Duration operator+(Duration& lhs, Duration& rhs) {
	return Duration(lhs.hour + rhs.hour, lhs.minute + rhs.minute);
}

bool operator<(const Duration& lhs, const Duration& rhs) {
	if (lhs.hour == rhs.hour) {
		return lhs.minute < rhs.minute;
	}
	return lhs.hour < rhs.hour;
}

void PrintVector(const std::vector <Duration>& durs) {
	for (const auto& d : durs) {
		std::cout << d << " ";
	}
	std::cout << std::endl;
}

int main() {
	std::stringstream ss("2:50");
	Duration dur1;
	ss >> dur1;
	Duration dur2 = { 0, 35 };
	Duration dur3 = dur1 + dur2;
	std::vector <Duration> v {dur3, dur1, dur2};
	PrintVector(v);
	std::cout << dur1 << std::endl;
	std::sort(begin(v), end(v));
	PrintVector(v);
	return 0;
}