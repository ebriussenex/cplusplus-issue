#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <array>


class Stats {
public:
	Stats();
	void AddMethod(std::string_view method);
	void AddUri(std::string_view uri);
	const std::map<std::string_view, int>& GetMethodStats() const;
	const std::map<std::string_view, int>& GetUriStats() const;
private:
	std::map<std::string_view, int> uri_stat_;
	std::map<std::string_view, int> method_stat_;
};

HttpRequest ParseRequest(std::string_view line);