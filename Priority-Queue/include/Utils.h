#pragma once

#include <vector>
#include <random>
#include <array>

namespace Utils
{
	/*
	 * Formats a number with commas
	 */
	template<class T>
	inline std::string FormatWithCommas(T value)
	{
		std::stringstream ss;
		ss.imbue(std::locale(""));
		ss << std::fixed << std::setprecision(2) << value;
		return ss.str();
	}

	/*
	 * Compares dates in the format of MM/DD/YYYY
	 *
	 * Returns true if lhs is older
	 */
	inline bool CompareDates(char const *lhs, char const *rhs) {
		// Compare year
		if (std::lexicographical_compare(lhs + 6, lhs + 10, rhs + 6, rhs + 10))
			return true;
		if (!std::equal(lhs + 6, lhs + 10, rhs + 6))
			return false;
		// Years equal, compare month
		if (std::lexicographical_compare(lhs + 3, lhs + 5, rhs + 3, rhs + 5))
			return true;
		if (!std::equal(lhs + 3, lhs + 5, rhs + 3))
			return false;
		// Months equal, compare days
		return std::lexicographical_compare(lhs, lhs + 2, rhs, rhs + 2);
	}

	/*
	 * Generates and returns a random double in defined range. 
	 */
	inline double RandomDouble(const double min, const double max)
	{
		// Init RNG
		std::array<double, std::mt19937::state_size> seedData{};
		std::random_device rd;
		std::generate_n(seedData.data(), seedData.size(), std::ref(rd));
		std::seed_seq seq(std::begin(seedData), std::end(seedData));
		std::mt19937 gen(seq);

		// Get random number
		const std::uniform_real_distribution<double> dis(min, max);
		const auto n = dis(gen);
		return n;
	}

	/*
	 * Generates and returns a random integer in defined range.
	 */
	inline int RandomInt(const int min, const int max)
	{
		// Init RNG
		std::array<int, std::mt19937::state_size> seedData{};
		std::random_device rd;
		std::generate_n(seedData.data(), seedData.size(), std::ref(rd));
		std::seed_seq seq(std::begin(seedData), std::end(seedData));
		std::mt19937 gen(seq);

		// Get random number
		const std::uniform_int_distribution<int> dis(min, max);
		const auto n = dis(gen);
		return n;
	}

	/*
	 * Determines if a vector contains duplicates.
	 */
	template <typename T>
	bool DuplicatesExist(std::vector<T> &v)
	{
		auto it = std::unique(v.begin(), v.end());

		// False <--> Unique, True <--> Duplicates. 
		return ((it == v.end()) ? false : true);
	}
}
