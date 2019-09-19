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

using bsmap = std::map <std::string, std::vector <std::string>>;

enum class QueryType {
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query {
	QueryType type;
	std::string bus;
	std::string stop;
	std::vector<std::string> stops;
};

std::istream& operator >> (std::istream& is, Query& q) {
	std::string command, stop, bus;
	unsigned int stops_count;
	std::vector <std::string> stops;
	is >> command;
	if (command == "NEW_BUS") {
		q.type = QueryType::NewBus;
		is >> bus;
		is >> stops_count;
		for (size_t i = 0; i < stops_count; i++) {
			is >> stop;
			stops.push_back(stop);
		}
		q.bus = bus;
		q.stops = stops;
	}
	if (command == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		is >> stop;
		q.stop = stop;
	}
	if (command == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		is >> bus;
		q.bus = bus;
	}
	if (command == "ALL_BUSES") {
		q.type = QueryType::AllBuses;
	}
	return is;
}

struct BusesForStopResponse {
	std::string stop;
	std::vector <std::string> buses;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r) {
	bool first = true;
	//std::cout << r.buses.size() << "FUKC\n";
	if (!r.buses.size()) {
		os << "No stop";
		return os;
	}
	for (const auto& bus : r.buses) {
		if (!first) os << " ";
		os << bus;
		first = false;
	}
	return os;
}

struct StopsForBusResponse {
	std::string bus;
	std::vector <std::string> stops;
	bsmap buses_for_stop;
};

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r) {
	if (!r.bus.size()) {
		os << "No bus";
		return os;
	}
	for (const auto& stop : r.stops) {
		bool first = true;
		os << "Stop " + stop + ":";
		if (r.buses_for_stop.at(stop).size() == 1) os << " no interchange\n";
		else {
			for (const auto& bus : r.buses_for_stop.at(stop)) {
				if (bus != r.bus) {
					os << " " + bus;
				}
			}
			os << std::endl;
		}
	}
	return os;
}

struct AllBusesResponse {
	bsmap stops_for_bus;
};

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r) {
	if (!r.stops_for_bus.size()) os << "No buses";
	else {
		for (const auto& item : r.stops_for_bus) {
			os << "Bus " + item.first + ":";
			for (const auto& stop : item.second) {
				os << " " + stop;
			}
			os << std::endl;
		}
	}
	return os;
}

class BusManager {
public:
	void AddBus(const std::string& bus, const std::vector<std::string>& stops) {
		stops_for_bus[bus] = stops;
		for (const auto& stop : stops) {
			buses_for_stop[stop].push_back(bus);
		}
	}

	BusesForStopResponse GetBusesForStop(const std::string& stop) const {
		BusesForStopResponse resp;
		resp.stop = stop;
		if (!buses_for_stop.count(stop)){
			resp.buses = {};
			return resp;
	    }
		resp.buses = buses_for_stop.at(stop);
		return resp;
	}

	StopsForBusResponse GetStopsForBus(const std::string& bus) const {
		StopsForBusResponse resp;
		if (!stops_for_bus.count(bus)) return resp;
		resp.bus = bus;
		resp.stops = stops_for_bus.at(bus);
		resp.buses_for_stop = buses_for_stop;
		return resp;
	}

	AllBusesResponse GetAllBuses() const {
		AllBusesResponse resp;
		if (!buses_for_stop.size()) return resp;
		resp.stops_for_bus = stops_for_bus;
		return resp;
	}
private:
	bsmap buses_for_stop;
	bsmap stops_for_bus;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
	int query_count;
	Query q;

	BusManager bm;
	std::cin >> query_count;
	for (int i = 0; i < query_count; ++i) {
		std::cin >> q;
		switch (q.type) {
		case QueryType::NewBus:
			bm.AddBus(q.bus, q.stops);
			break;
		case QueryType::BusesForStop:
			std::cout << bm.GetBusesForStop(q.stop) << std::endl;
			break;
		case QueryType::StopsForBus:
			std::cout << bm.GetStopsForBus(q.bus) << std::endl;
			break;
		case QueryType::AllBuses:
			std::cout << bm.GetAllBuses() << std::endl;
			break;
		}
	}

	return 0;
}