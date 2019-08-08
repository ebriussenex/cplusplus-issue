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
		hour = h;
		minute = m;
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

int main() {
	std::stringstream ss("16:48");
	Duration dur1;
	ss >> dur1;
	std::cout << dur1;
	return 0;
}