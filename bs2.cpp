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
	int n, q, counter = 1;
	std::string str;
	std::cin >> n;
	std::map <std::vector<std::string>, int> bus;
	for (int i = 0; i < n; i++) {
		std::cin >> q;
		std::vector <std::string> stop;
		for (int j = 0; j < q; j++) {
			std::cin >> str;
			stop.push_back(str);
		}
		if (bus.count(stop) != 0) {
			std::cout << "Already exists for " << bus[stop] << std::endl;
		}
		else {
			bus[stop] = counter;
			std::cout << "New bus " << counter << std::endl; 
			counter++;
		}
	}
	system("PAUSE");
	return 0;
}