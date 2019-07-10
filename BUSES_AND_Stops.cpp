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
	int n, q;
	std::string command, command_arg;
	std::cin >> n;
	std::map <std::string, std::vector <std::string> > bs;
	std::map <std::string, std::vector <std::string> > sb;
	for (int i = 0; i < n; i++) {
		std::cin >> command;
		if (command == "NEW_BUS") {
			std::cin >> command_arg >> q;
			bs[command_arg];
			for (int j = 0; j < q; j++) {
				std::string temp;
				std::cin >> temp;
				bs[command_arg].push_back(temp);
				sb[temp].push_back(command_arg);
			}
		}
		if (command == "BUSES_FOR_STOP") {
			std::cin >> command_arg;
			if (sb.count(command_arg) == 0) {
				std::cout << "No stop\n";
			}
			else {
				for (auto bus : sb[command_arg]) {
					std::cout << bus << " ";
				}
				std::cout << std::endl;
			}
		}
		if (command == "STOPS_FOR_BUS") {
			std::cin >> command_arg;
			if (bs.count(command_arg) == 0) {
				std::cout << "No bus\n";
			}
			else {
				for (auto stop : bs[command_arg]) {
					std::cout << "Stop " << stop << ": ";
					if (sb[stop].size() == 1)	std::cout << "no interchange\n";
					else {
						for (auto bus : sb[stop]) {
							if (bus != command_arg) {
								std::cout << bus << " ";
							}
						}
						std::cout << std::endl;
					}
				}
			}
		}
		if (command == "ALL_BUSES") {
			if (bs.size() == 0) {
				std::cout << "No buses\n";
			}
			else {
				for (auto bus : bs) {
					std::cout << "Bus " << bus.first << ": ";
					for (auto stop : bus.second) {
						std::cout << stop << " ";
					}
					std::cout << std::endl;
				}
			}
		}
	}
	system("PAUSE");
	return 0;
}