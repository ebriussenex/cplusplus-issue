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

void SendSms(const std::string& number, const std::string& message) {
	std::cout << "Send message " << message << " to number" << number;
}
void SendEmail(const std::string& email, const std::string& message) {
	std::cout << "Send message " << message << " to email" << email;
}

class INotifier {
public:
	virtual void Notify(const std::string& message) const = 0;
};

class SmsNotifier : public INotifier {
public:
	SmsNotifier(const std::string& number) : number_(number){}
	void Notify(const std::string& message) const override {
		SendSms(number_, message);
	}
private:
	std::string number_;
};

class EmailNotifier : public INotifier {
public:
	EmailNotifier(const std::string& email) : email_(email) {}
	void Notify(const std::string& message) const override {
		SendEmail(email_, message);
	}
private:
	std::string email_;
};

void Notify(const INotifier& notifier, const std::string& message) {
	notifier.Notify(message);
}

int main() {
	SmsNotifier sms{ "+7-495-777-77-77" };
	EmailNotifier email{ "na-derevnyu@dedushke.ru" };

	Notify(sms, "I have White belt in C++");
	Notify(email, "And want a Yellow one");
	return 0;
}

