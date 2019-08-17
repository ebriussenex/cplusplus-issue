#include "responses.h"

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