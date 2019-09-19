#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <cstdint>

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

//std::ostream & operator<<(std::ostream& stream, const std::deque <std::string>& d) {
//	for (const auto& item : d) {
//		if (item == "*" || item == "+" || item == "-" || item == "/") {
//			stream << " " << item << " ";
//		}
//		else stream << item;
//	}
//}

enum class Sign {
	ADD,
	SUB,
	MULT,
	DIV
};

class Expression {
public:
	Expression() {
		sign_ = Sign::MULT;
		current_sign_ = '*';
		last_sign_ = '*';
	}
	Sign GetSign() const {
		return sign_;
	}
	char GetLastSign() const {
		return last_sign_;
	}
	char GetCurrentSign() const {
		return current_sign_;
	}
	std::deque <std::string> GetExpression() const {
		return expression_;
	}

	void AddNumber(const int number) {
		expression_.push_back(std::to_string(number));
	}
	void AssignSign(const char sign) {
		if (sign == '+') {
			sign_ = Sign::ADD;
		}
		if (sign == '-') {
			sign_ = Sign::SUB;
		}
		if (sign == '*') {
			sign_ = Sign::MULT;
		}
		if (sign == '/') {
			sign_ = Sign::DIV;
		}
	}
	void AddBrackets() {
		expression_.push_front("(");
		expression_.push_back(")");
	}
	void AddSign(const char sign) {
		last_sign_ = current_sign_;
		current_sign_ = sign;
		if (last_sign_ != '*' && last_sign_ != '/' && (current_sign_ == '/' || current_sign_ == '*')) {
			expression_.push_front("(");
			expression_.push_back(")");
		}
		expression_.push_back(std::string(1, sign));
	}
private:
	char last_sign_;
	char current_sign_;
	Sign sign_;
	std::deque <std::string> expression_;
};

int main() {
	Expression ex;
	unsigned int n = 0;
	char sign;
	int j = 0;
	std::cin >> j >> n;
	ex.AddNumber(j);
	for (size_t i = 0; i < n; i++) {
		std::cin >> sign;
		std::cin >> j;
		ex.AddSign(sign);
		ex.AddNumber(j);
	}
	std::deque <std::string> d = ex.GetExpression();
	for (const auto& item : d) {
		if (item == "*" || item == "+" || item == "-" || item == "/") {
			std::cout << " " << item << " ";
		}
		else std::cout << item;
	}
	/*std::cout << d;*/
	return 0;
}

