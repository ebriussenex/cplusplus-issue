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
#include "profile.h"

class Event {
public:
	Event(const std::string& hotel_name, const int64_t& time, const uint32_t& client_id, const uint32_t& room_count) :
	time_(time), hotel_name_(hotel_name), client_id_(client_id), room_count_(room_count){}
	int64_t time_;
	std::string hotel_name_;
	uint32_t client_id_;
	uint32_t room_count_;
};

class EventManager {
public:
	EventManager()  {}
	void Add(const std::string& hotel_name, const int64_t& time, const uint32_t& client_id, const uint32_t& room_count) {//amortized o(q)
		Adjust(time);
		//events_[hotel_name].push({ time, {client_id, room} });//o(1)
		events_.push({ hotel_name, time, client_id, room_count });
		rooms_[hotel_name] += room_count;
		clients_[hotel_name][client_id]++;
	}
	void Rooms(const std::string& hotel_name) {
		std::cout << rooms_[hotel_name] << '\n';
	}
	void Clients(const std::string& hotel_name) {
		std::cout << clients_[hotel_name].size() << '\n';
	}
private:
	void Adjust(const int64_t& time) {
		while (!events_.empty() && events_.front().time_ <= time - 86400) {
			rooms_[events_.front().hotel_name_] -= events_.front().room_count_;
			clients_[events_.front().hotel_name_][events_.front().client_id_]--;
			if (clients_[events_.front().hotel_name_][events_.front().client_id_] == 0) {
				clients_[events_.front().hotel_name_].erase(events_.front().client_id_);
			}
			events_.pop();
		}
	}
	std::map<std::string, uint32_t> rooms_;
	std::map<std::string, std::map<uint32_t, uint32_t>> clients_;
	//std::map<std::string, std::queue<std::pair<int64_t, std::pair<uint32_t, uint32_t>>>> events_;// time client_id rooms
	std::queue <Event> events_;
};



int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	EventManager manager;
	size_t query_count;
	std::cin >> query_count;
	for (size_t query_id = 0; query_id < query_count; query_id++) {
		std::string query_type;
		std::cin >> query_type;
		if (query_type == "BOOK") {
			//BOOK time hotel_name client_id room_count
			long long int time;
			std::string hotel_name;
			int client_id;
			int room_count;
			std::cin >> time >> hotel_name >> client_id >> room_count;
			manager.Add(hotel_name, time, client_id, room_count);
		}
		if (query_type == "CLIENTS") {
			std::string hotel_name;
			std::cin >> hotel_name;
			manager.Clients(hotel_name);
		}
		if (query_type == "ROOMS") {
			std::string hotel_name;
			std::cin >> hotel_name;
			manager.Rooms(hotel_name);
		}
	}
	return 0;
}