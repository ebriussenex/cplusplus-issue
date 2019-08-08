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

std::set<std::string> BuildMapValuesSet(const std::map<int, std::string>& m) {
	std::set <std::string> s;
	for (auto i : m) {
		s.insert(i.second);
	}
	return s;
}

int main() {
	int n;
	std::cin >> n;
	std::string command, worda, wordb;
	std::set <std::set <std::string>> s;
	std::map <std::string, std::set <std::string>> m;
	for (int i = 0; i < n; i++) {
		std::cin >> command;
		if (command == "ADD") {
			std::set <std::string> temps;
			std::cin >> worda >> wordb;
			m[worda].insert(wordb);
			m[wordb].insert(worda);
		}
		if (command == "COUNT") {
			std::cin >> worda;
			std::cout << m[worda].size() << std::endl;
		}
		if (command == "CHECK") {
			std::cin >> worda >> wordb;
			if (m[worda].count(wordb)) {
				std::cout << "YES\n";
			}
			else  std::cout << "NO\n";
		}
	}
	system("pause");
	return 0;
}