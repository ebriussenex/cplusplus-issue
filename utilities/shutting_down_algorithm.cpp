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

struct Node {
	virtual int Evaluate() const = 0;
};

struct Value : public Node {
	Value(char digit) : _value(digit - '0') {}

	int Evaluate() const override { return _value; }

private:
	const uint8_t _value;
};

struct Variable : public Node {
	Variable(const int& x) : _x(x) {}

	int Evaluate() const override { return _x; }

private:
	const int& _x;
};

struct Op : public Node {
	Op(char value)
		: precedence([value] {
		if (value == '*') {
			return 2;
		}
		else {
			return 1;
		}
			}()),
		_op(value) {}

			const uint8_t precedence;

			int Evaluate() const override {
				if (_op == '*') {
					return _left->Evaluate() * _right->Evaluate();
				}
				else if (_op == '+') {
					return _left->Evaluate() + _right->Evaluate();
				}
				else if (_op == '-') {
					return _left->Evaluate() - _right->Evaluate();
				}

				return 0;
			}

			void SetLeft(std::shared_ptr<Node> node) { _left = node; }
			void SetRight(std::shared_ptr<Node> node) { _right = node; }

private:
	const char _op;
	std::shared_ptr<const Node> _left, _right;
};

template <class Iterator>
std::shared_ptr<Node> Parse(Iterator token, Iterator end, const int& x) {
	// Empty expression
	if (token == end) {
		return make_shared<Value>('0');
	}

	stack<shared_ptr<Node>> values;
	stack<shared_ptr<Op>> ops;

	auto PopOps = [&](int precedence) {
		while (!ops.empty() && ops.top()->precedence >= precedence) {
			auto value1 = values.top();
			values.pop();
			auto value2 = values.top();
			values.pop();
			auto op = ops.top();
			ops.pop();

			op->SetRight(value1);
			op->SetLeft(value2);

			values.push(op);
		}
	};

	while (token != end) {
		const auto& value = *token;
		if (value >= '0' && value <= '9') {
			values.push(make_shared<Value>(value));
		}
		else if (value == 'x') {
			values.push(make_shared<Variable>(x));
		}
		else if (value == '*') {
			PopOps(2);
			ops.push(make_shared<Op>(value));
		}
		else if (value == '+' || value == '-') {
			PopOps(1);
			ops.push(make_shared<Op>(value));
		}

		++token;
	}

	while (!ops.empty()) {
		PopOps(0);
	}

	return values.top();
}

int main() {
	std::string tokens;
	std::cout << "Enter expression: ";
	std::getline(std::cin, tokens);

	int x = 0;
	auto node = Parse(tokens.begin(), tokens.end(), x);

	std::cout << "Enter x: ";
	while (std::cin >> x) {
		std::cout << "Expression value: " << node->Evaluate() << std::endl;
		std::cout << "Enter x: ";
	}

	return 0;
}

