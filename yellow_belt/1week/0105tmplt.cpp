#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>
#include <exception>
#include <cassert>
#include <cstdint>

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

#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <functional>

template <typename Key, typename Value>
Value& GetRefStrict(std::map <Key, Value>& m, const Key& key);

template <typename Key, typename Value>
Value& GetRefStrict(std::map <Key, Value>& m, const Key& key) {
	if (!m.count(key)) { throw std::runtime_error("Runtime_error"); };
	return m.at(key);
}

int main() {
	/*try {
		std::map<int, std::string> m = { {0, "value"} };
		std::string& item = GetRefStrict(m, 0);
		item = "newvalue";
		std::cout << m[0] << std::endl;
	}
	catch (std::runtime_error& ex) {
		std::cout << ex.what();
	}*/
	return 0;
}