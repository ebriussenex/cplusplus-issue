#pragma once

#include "responses.h"

#include <vector>
#include <string>
#include <map>

class BusManager {
public:
	void AddBus(const std::string& bus, const std::vector<std::string>& stops);
	BusesForStopResponse GetBusesForStop(const std::string& stop) const;
	StopsForBusResponse GetStopsForBus(const std::string& bus) const;
	AllBusesResponse GetAllBuses() const;
private:
	bsmap buses_for_stop;
	bsmap stops_for_bus;
};