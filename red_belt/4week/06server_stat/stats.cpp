#pragma once
#include "stats.h"

Stats::Stats()//«GET», «POST», «PUT», «DELETE», UNKNOWN, «/», «/order», «/product», «/basket», «/help», unknown
{
	method_stat_["GET"] = 0;
	method_stat_["PUT"] = 0;
	method_stat_["POST"] = 0;
	method_stat_["DELETE"] = 0;
	method_stat_["UNKNOWN"] = 0;
	uri_stat_["/"] = 0;
	uri_stat_["/order"] = 0;
	uri_stat_["/product"] = 0;
	uri_stat_["/basket"] = 0;
	uri_stat_["/help"] = 0;
	uri_stat_["unknown"] = 0;

}

void Stats::AddMethod(std::string_view method)//«GET», «POST», «PUT», «DELETE», UNKNOWN
{
	if (method != "GET" && method != "POST" && method != "PUT" && method != "DELETE") {
		method_stat_["UNKNOWN"]++;
	}
	else method_stat_[method]++;
}

void Stats::AddUri(std::string_view uri)//«/», «/order», «/product», «/basket», «/help», unknown
{
	if (uri != "/" && uri != "/order" && uri != "/product" && uri != "/basket" && uri != "/help") {
		uri_stat_["unknown"]++;
	}
	else uri_stat_[uri]++;
}

const std::map<std::string_view, int>& Stats::GetMethodStats() const
{
	return method_stat_;
}

const std::map<std::string_view, int>& Stats::GetUriStats() const
{
	return uri_stat_;
}

HttpRequest ParseRequest(std::string_view line)
{
	HttpRequest result;
	auto temp_pos = line.find_first_not_of(' ');
	if (temp_pos > 0) {
		line.remove_prefix(temp_pos);
	}
	temp_pos = line.find(' ');
	result.method = line.substr(0, temp_pos);
	line.remove_prefix(temp_pos);
	temp_pos = line.find_first_not_of(' ');
	if (temp_pos > 0) {
		line.remove_prefix(temp_pos);
	}
	temp_pos = line.find(' ');
	result.uri = line.substr(0, temp_pos);
	line.remove_prefix(temp_pos);
	temp_pos = line.find_first_not_of(' ');
	if (temp_pos > 0) {
		line.remove_prefix(temp_pos);
	}
	temp_pos = line.find(' ');
	result.protocol = line.substr(0, temp_pos);
	return result;
}
