#include "query.h"

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