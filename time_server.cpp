#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>
#include <exception>

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

std::string AskTimeServer() {
	/* ƒл€ тестировани€ повставл€йте сюда код, реализующий различное поведение этой функии:
	   * нормальный возврат строкового значени€
	   * выброс исключени€ system_error
	   * выброс другого исключени€ с сообщением.
	*/
	return "ok";
}

class TimeServer {
public:
	std::string GetCurrentTime() {
		try {
			std::string temp = AskTimeServer();
			LastFetchedTime = temp;
			return temp;
		}
		catch (std::system_error& ex) {
			return LastFetchedTime;
		}
		catch (...) {
			throw;
		}
	}

private:
	std::string LastFetchedTime = "00:00:00";
};

int main() {
	// ћен€€ реализацию функции AskTimeServer, убедитесь, что это код работает корректно
	TimeServer ts;
	try {
		std::cout << ts.GetCurrentTime() << std::endl;
	}
	catch (std::exception& e) {
		std::cout << "Exception got: " << e.what() << std::endl;
	}
	return 0;
}