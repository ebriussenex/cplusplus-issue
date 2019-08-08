#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>

#include <ios>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <fstream>
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

//struct Image {
//	double quality;
//	double freshness;
//	double rating;
//};
//
//struct Params {
//	double a;
//	double b;
//	double c;
//};

class FunctionPart {
public:
	FunctionPart(char new_operation, double new_value) {
		operation = new_operation;
		value = new_value;
	}
	double Apply(double source_value) const {
		if (operation == '+')	return source_value + value;
		else if (operation == '-')	return source_value - value;
		else if (operation == '*')	return source_value * value;
		else if (operation == '/')	return source_value / value;
	}
	void Invert() {
		if (operation == '+')	operation = '-';
		else if (operation == '-')	operation = '+';
		else if (operation == '*')	operation = '/';
		else if (operation == '/')	operation = '*';
	}
private:
	char operation;
	double value;
};

class Function {
public:
	Function(){}
	void AddPart(char operation, double value) {
		parts.push_back({ operation, value });
	}
	double Apply(double value) const {
		for (const FunctionPart& part : parts) {
			value = part.Apply(value);
		}
		return value;
	}
	void Invert() {
		for (FunctionPart& part : parts) {
			part.Invert();
		}
		reverse(parts.begin(), parts.end());
	}
private:
	std::vector <FunctionPart> parts;
};
//
//Function MakeWeightFunction(const Params& params,
//	const Image& image) {
//	Function function;
//	function.AddPart('*', params.a);
//	function.AddPart('-', image.freshness * params.b);
//	function.AddPart('+', image.rating * params.c);
//	return function;
//}
//
//double ComputeImageWeight(const Params& params, const Image& image) {
//	Function function = MakeWeightFunction(params, image);
//	return function.Apply(image.quality);
//}
//
//double ComputeQualityByWeight(const Params& params,
//	const Image& image,
//	double weight) {
//	Function function = MakeWeightFunction(params, image);
//	function.Invert();
//	return function.Apply(weight);
//}
//
//int main() {
//	Image image = { 10, 2, 6 };
//	Params params = { 4, 2, 6 };
//	std::cout << ComputeImageWeight(params, image) << std::endl;
//	std::cout << ComputeQualityByWeight(params, image, 52) << std::endl;
//	return 0;
//}