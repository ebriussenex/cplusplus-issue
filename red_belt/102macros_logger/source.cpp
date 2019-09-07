#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <cstdint>
#include <memory>

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
#include <tuple>
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
#include <numeric>

#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <functional>

#include "test_runner.h"

class Logger {
public:
	explicit Logger(std::ostream& output_stream) : os(output_stream) { // @suppress("Class members should be properly initialized")
	}
	void SetLogLine(bool value) { log_line = value; }
	void SetLogFile(bool value) { log_file = value; }
	void Log(const std::string& message) {
		if (log_line && log_file) {
			os << file_ << ":" << line_ << " ";
		}
		else if (log_file) {
			os << file_ << " ";
		}
		else if (log_line) {
			os << "Line " << line_ << " ";
		}
		os << message << std::endl;
	}
	void SetFile(const std::string& file) {
		file_ = file;
	}
	void SetLine(const int& line) {
		line_ = line;
	}

private:
	std::ostream& os;
	bool log_line = false;
	bool log_file = false;
	std::string file_;
	int line_;
};

#define LOG(logger, message){		\
		logger.SetLine(__LINE__);	\
		logger.SetFile(__FILE__);	\
		logger.Log(message);		\
}

void TestLog() {
#line 1 "logger.cpp"

	std::ostringstream logs;
	Logger l(logs);
	LOG(l, "hello");

	l.SetLogFile(true);
	LOG(l, "hello");

	l.SetLogLine(true);
	LOG(l, "hello");

	l.SetLogFile(false);
	LOG(l, "hello");

	std::string expected = "hello\n";
	expected += "logger.cpp hello\n";
	expected += "logger.cpp:10 hello\n";
	expected += "Line 13 hello\n";
	ASSERT_EQUAL(logs.str(), expected);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestLog);
}
