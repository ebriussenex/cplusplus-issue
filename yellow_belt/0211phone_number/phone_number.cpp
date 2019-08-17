//#pragma once
#include "phone_number.h"
#include <sstream>

PhoneNumber::PhoneNumber(const std::string& international_number)
{
	std::stringstream ss;
	ss.str(international_number);
	if (ss.peek() != '+') throw std::invalid_argument("Wrong sign, should be +");
	ss.ignore(1);
	std::getline(ss, country_code_, '-');
	std::getline(ss, city_code_, '-');
	std::getline(ss, local_number_);
	if (!country_code_.size()) throw std::invalid_argument("Country code is empty!");
	if (!city_code_.size()) throw std::invalid_argument("City code is empty!");
	if (!local_number_.size()) throw std::invalid_argument("Local number is empty!");
}

std::string PhoneNumber::GetCountryCode() const
{
	return country_code_;
}

std::string PhoneNumber::GetCityCode() const
{
	return city_code_;
}

std::string PhoneNumber::GetLocalNumber() const
{
	return local_number_;
}

std::string PhoneNumber::GetInternationalNumber() const
{
	return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}
