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

class Figure {
public:
	Figure() {}
	virtual std::string Name() const = 0;
	virtual double Perimeter() const = 0;
	virtual double Area() const = 0;
private:
	double square_;
	double perimeter_;
};

class Triangle : public Figure {
public:
	Triangle(int& a, int& b, int& c) :
		a_(a), b_(b), c_(c) {}
	std::string Name() const override {
		return "TRIANGLE";
	}
	double Perimeter() const override {
		return a_ + b_ + c_;
	}
	double Area() const override {
		double half_perimeter = Perimeter() / 2;
		return sqrt(half_perimeter * (half_perimeter - a_) * (half_perimeter - b_) * (half_perimeter - c_));
	}
private:
	int a_, b_, c_;
};

class Rect : public Figure {
public:
	Rect(int& h, int& w) :
		h_(h), w_(w) {}
	std::string Name() const override {
		return "RECT";
	}
	double Perimeter() const override {
		return 2 * (h_ + w_);
	}
	double Area() const override {
		return h_ * w_;
	}
private:
	int h_, w_;
};

class Circle : public Figure {
public:
	Circle(int& r) :
		r_(r) {}
	std::string Name() const override {
		return "CIRCLE";
	}
	double Perimeter() const override {
		return 2 * k_pi_ * r_;
	}
	double Area() const override {
		return k_pi_ * r_ * r_;
	}
private:
	const double k_pi_ = 3.14;
	int r_;
};


std::shared_ptr<Figure> CreateFigure(std::istream& is) {
	std::string name;
	is >> name;
	if (name == "CIRCLE") {
		int r;
		is >> r;
		return std::make_shared<Circle>(r);
	}
	if (name == "RECT") {
		int h, w;
		is >> h >> w;
		return std::make_shared<Rect>(h, w);
	}
	if (name == "TRIANGLE") {
		int a, b, c;
		is >> a >> b >> c;
		return std::make_shared<Triangle>(a, b, c);
	}
}

int main() {
	std::vector<std::shared_ptr<Figure>> figures;
	for (std::string line; std::getline(std::cin, line); ) {
		std::istringstream is(line);

		std::string command;
		is >> command;
		if (command == "ADD") {
			figures.push_back(CreateFigure(is));
		}
		else if (command == "PRINT") {
			for (const auto& current_figure : figures) {
				std::cout << std::fixed << std::setprecision(3)
					<< current_figure->Name() << " "
					<< current_figure->Perimeter() << " "
					<< current_figure->Area() << std::endl;
			}
		}
	}
	return 0;
}

