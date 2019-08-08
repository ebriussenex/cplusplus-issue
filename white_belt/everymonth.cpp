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
#include <utility>
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

std::vector<int> Reversed(const std::vector<int>& v) {
	std::vector <int> reversed;
	for (int i = v.size() - 1; i > -1; i--) {
		reversed.push_back(v[i]);
	}
	return reversed;
}

void print(std::vector<bool>& a) {
	for (auto i : a) {
		std::cout << "++" << a[i] << std::endl;
	}
}

int main(int argc, char ** argv) {
	int n, command_arg;
	std::string command, work;
	std::cin >> n;
	std::vector <int> year = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	std::vector <std::vector <std::string> > month(31);
	int j = 0;
	for (int i = 0; i < n; i++) {
		std::cin >> command;
		if (command == "ADD") {
			std::cin >> command_arg >> work;
			month[command_arg - 1].push_back(work);
		}
		if (command == "NEXT") {
			if (j == 11) {
				j = 0;
			}
			else j++;
			if (year[j] == year[j - 1]) {
				pass;
			}
			if (year[j] > year[j - 1]) {
				month.resize(year[j]);
			}
			if (year[j] < year[j - 1]) {
				if (year[j] == 28) {//to february case
					std::vector <std::string> temp1 = month[30];
					std::vector <std::string> temp2 = month[29];
					std::vector <std::string> temp3 = month[28];
					month.resize(28);
					month[27].insert(month[27].end(), temp1.begin(), temp1.end());
					month[27].insert(month[27].end(), temp2.begin(), temp2.end());
					month[27].insert(month[27].end(), temp3.begin(), temp3.end());
				}
				else  if (year[j] == 30) {
					std::vector <std::string> temp = month[30];
					month.resize(30);
					month[29].insert(month[29].end(), temp.begin(), temp.end());
				}
			}
		}
		if (command == "DUMP") {
			std::cin >> command_arg;
			std::cout << month[command_arg - 1].size() << " ";
			for (auto w : month[command_arg - 1]) {
				std::cout << w << " ";
			}
			std::cout << std::endl;
		}
	}
	system("PAUSE");
	return 0;
}