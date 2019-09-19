#pragma once 

#include <iostream>
#include <vector>
#include <map>
#include <string>

using bsmap = std::map <std::string, std::vector <std::string>>;

struct BusesForStopResponse {
	std::string stop;
	std::vector <std::string> buses;
};
std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);
struct StopsForBusResponse {
	std::string bus;
	std::vector <std::string> stops;
	bsmap buses_for_stop;
};
std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);
struct AllBusesResponse {
	bsmap stops_for_bus;
};
std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);