#pragma once

#include <vector>
#include <random>
#include <array>

namespace COSC
{
	/*
	 * Generates and returns a random double in defined range. 
	 */
	inline double Rand(const double min, const double max)
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
	inline int Rand(const int min, const int max)
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
