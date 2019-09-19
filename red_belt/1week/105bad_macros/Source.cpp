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

int main() {
	TestRunner tr;
	tr.RunTest([] {
		std::ostringstream output;
		PRINT_VALUES(output, 5, "red belt");
		ASSERT_EQUAL(output.str(), "5\nred belt\n");
		/*if(true) PRINT_VALUES(output, 4, "a");
		ASSERT_EQUAL(output.str(), "4\na\n");
		if (false) PRINT_VALUES(output, 3, "c");
		else PRINT_VALUES(output, 2, "h");
		ASSERT_EQUAL(output.str(), "2\nh\n");*/
		}, "PRINT_VALUES usage example");
}
