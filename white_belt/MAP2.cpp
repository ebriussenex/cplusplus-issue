#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>
#include <iostream>
#include <stack>
#include <queue>
#include <iomanip>
#include <vector>
#include <algorithm>
//#include <utility>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <fstream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <list>
#include <cstring>

std::vector <std::string> PalindromFilter(std::vector <std::string> words, int minLength) {
	std::vector <std::string> ans;
	bool flag = true;
	for (auto word : words) {
		int n = word.length() - 1;
		for (int i = 0; i < n / 2 + 1; i++) {
			if (word[i] == word[n - i]);
			else {
				flag = false;
			}
		}
		if (flag && word.length() >= minLength) {
			ans.push_back(word);
		}
		flag = true;
	}
	return ans;
}

bool IsPalindrom(std::string word) {
	int n = word.length() - 1;
	for (int i = 0; i < n / 2 + 1; i++) {
		if (word[i] == word[n - i]);
		else {
			return false;
		}
	}
	return true;
}

void UpdateIfGreater(const int& first, int& second) {
	if (first > second) {
		second = first;
	}
}

void MoveStrings(std::vector <std::string>& source, std::vector <std::string>& destination) {
	for (auto s : source) {
		destination.push_back(s);
	}
	source.clear();
}

//void Reverse(std::vector<int>& v) {
//	std::reverse(std::begin(v), std::end(v));
//}

int main() {
	int n;
	std::cin >> n;
	std::string command, command_arg_a, command_arg_b, old_name = "";
	std::map <std::string, std::string> countries;
	bool ex = false, same = false;
	for (int i = 0; i < n; i++) {
		std::cin >> command;
		if (command == "CHANGE_CAPITAL") {
			std::cin >> command_arg_a >> command_arg_b;
			ex = (countries.count(command_arg_a) > 0);
			old_name = countries[command_arg_a];
			same = (countries[command_arg_a] == command_arg_b);
			countries[command_arg_a] = command_arg_b;
			if (ex) {
				if (same) {
					std::cout << "Country " << command_arg_a << " hasn't changed its capital\n";
				}
				else {
					std::cout << "Country " << command_arg_a << " has changed its capital from " << old_name << " to " << command_arg_b << std::endl;
				}
			}
			else {
				std::cout << "Introduce new country " << command_arg_a << " with capital " << command_arg_b << std::endl;
			}
			ex = false;
			same = false;
		}
		if (command == "RENAME") {
			std::cin >> command_arg_a >> command_arg_b;
			if (countries.count(command_arg_a) == 0 || command_arg_a == command_arg_b || countries.count(command_arg_b) > 0) {
				std::cout << "Incorrect rename, skip" << std::endl;
			}
			else {
				countries[command_arg_b] = countries[command_arg_a];
				countries.erase(command_arg_a);
				std::cout << "Country " << command_arg_a << " with capital " << countries[command_arg_b] << " has been renamed to " << command_arg_b << std::endl;
			}
		}
		if (command == "ABOUT") {
			std::cin >> command_arg_a;
			if (countries.count(command_arg_a) == 0) std::cout << "Country " << command_arg_a << " doesn't exist\n";
			else  std::cout << "Country " << command_arg_a << " has capital " << countries[command_arg_a] << std::endl;
		}
		if (command == "DUMP") {
			if (countries.size() == 0) std::cout << "There are no countries in the world\n";
			else {
				for (auto i : countries) {
					if (i.first != "" && i.second != "") {
						std::cout << i.first << "/" << i.second << " ";
					}
				}
				std::cout << std::endl;
			}
		}
	}
	system("PAUSE");
	return 0;
}