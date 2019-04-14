#pragma once

#include <string>
#include <iomanip>
#include <sstream>

#include "Utils.h"

class Client    
{
public:
	Client() = default;

	Client(std::string name, std::string dob, const double balance)
		: m_name(std::move(name)), m_balance(balance), m_dateOfBirth(std::move(dob)) {}
private:
	std::string m_name;
	double m_balance;
	std::string m_dateOfBirth;

	friend std::ostream &operator<<(std::ostream &os, const Client &obj)
	{
		return os
			<< std::left << "[ Name: " << std::left << std::setw(22) << obj.m_name
			<< std::left << "| Date of Birth: " << std::left << std::setw(11) << obj.m_dateOfBirth
			<< std::left << "| Balance: $" << std::right << std::setw(10) << Utils::FormatWithCommas(obj.m_balance) << " ]";
	}

	friend bool operator<(const Client &lhs, const Client &rhs)
	{
		auto left = lhs.m_dateOfBirth;
		auto right = rhs.m_dateOfBirth;
		return Utils::CompareDates(right.c_str(), left.c_str());
	}

	friend bool operator>(const Client &lhs, const Client &rhs)
	{
		auto left = lhs.m_dateOfBirth;
		auto right = rhs.m_dateOfBirth;
		return Utils::CompareDates(left.c_str(), right.c_str());
	}
};
