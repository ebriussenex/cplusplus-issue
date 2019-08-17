#include "bus_manager.h"

void BusManager::AddBus(const std::string& bus, const std::vector<std::string>& stops) {
	stops_for_bus[bus] = stops;
	for (const auto& stop : stops) {
		buses_for_stop[stop].push_back(bus);
	}
}

BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) const {
	BusesForStopResponse resp;
	resp.stop = stop;
	if (!buses_for_stop.count(stop)) {
		resp.buses = {};
		return resp;
	}
	resp.buses = buses_for_stop.at(stop);
	return resp;
}

StopsForBusResponse BusManager::GetStopsForBus(const std::string& bus) const {
	StopsForBusResponse resp;
	if (!stops_for_bus.count(bus)) return resp;
	resp.bus = bus;
	resp.stops = stops_for_bus.at(bus);
	resp.buses_for_stop = buses_for_stop;
	return resp;
}

AllBusesResponse BusManager::GetAllBuses() const {
	AllBusesResponse resp;
	if (!buses_for_stop.size()) return resp;
	resp.stops_for_bus = stops_for_bus;
	return resp;
}