#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <cstdint>
#include <memory>
#include <random>

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
#include <array>
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
#include <string_view>
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
#include "profile.h"
#include "stats.h"
#include "http_request.h"

Stats ServeRequests(std::istream & input) {
	Stats result;
	for (std::string line; std::getline(input, line); ) {
		const HttpRequest req = ParseRequest(line);
		result.AddUri(req.uri);
		result.AddMethod(req.method);
	}
	return result;
}

void TestBasic() {
	const std::string input =
		R"(GET / HTTP/1.1
    POST /order HTTP/1.1
    POST /product HTTP/1.1
    POST /product HTTP/1.1
    POST /product HTTP/1.1
    GET /order HTTP/1.1
    PUT /product HTTP/1.1
    GET /basket HTTP/1.1
    DELETE /product HTTP/1.1
    GET / HTTP/1.1
    GET / HTTP/1.1
    GET /help HTTP/1.1
    GET /upyachka HTTP/1.1
    GET /unexpected HTTP/1.1
    HEAD / HTTP/1.1)";

	const std::map<std::string_view, int> expected_method_count = {
	  {"GET", 8},
	  {"PUT", 1},
	  {"POST", 4},
	  {"DELETE", 1},
	  {"UNKNOWN", 1},
	};
	const std::map<std::string_view, int> expected_url_count = {
	  {"/", 4},
	  {"/order", 2},
	  {"/product", 5},
	  {"/basket", 1},
	  {"/help", 1},
	  {"unknown", 2},
	};

	std::istringstream is(input);
	const Stats stats = ServeRequests(is);

	ASSERT_EQUAL(stats.GetMethodStats(), expected_method_count);
	ASSERT_EQUAL(stats.GetUriStats(), expected_url_count);
}

void TestAbsentParts() {

	const std::map<std::string_view, int> expected_method_count = {
	  {"GET", 0},
	  {"PUT", 0},
	  {"POST", 0},
	  {"DELETE", 0},
	  {"UNKNOWN", 0},
	};
	const std::map<std::string_view, int> expected_url_count = {
	  {"/", 0},
	  {"/order", 0},
	  {"/product", 0},
	  {"/basket", 0},
	  {"/help", 0},
	  {"unknown", 0},
	};
	const Stats default_constructed;

	ASSERT_EQUAL(default_constructed.GetMethodStats(), expected_method_count);
	ASSERT_EQUAL(default_constructed.GetUriStats(), expected_url_count);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	TestRunner tr;
	RUN_TEST(tr, TestBasic);
	RUN_TEST(tr, TestAbsentParts);
	return 0;
}
