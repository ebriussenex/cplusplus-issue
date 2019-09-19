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

#define PRINT_VALUES(out, x, y)\
out << (x) << '\n' << (y) << '\n' \

#define UNIQ_ID_3(line) var##line
#define UNIQ_ID_2(line) UNIQ_ID_3(line)
#define UNIQ_ID UNIQ_ID_2(__LINE__)

int main() {
	int UNIQ_ID = 0;
	std::string UNIQ_ID = "hello";
	std::vector<std::string> UNIQ_ID = { "hello", "world" };
	std::vector<int> UNIQ_ID = { 1, 2, 3, 4 };
}