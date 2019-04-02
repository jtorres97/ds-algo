#pragma once

#include <random>
#include <iostream>
#include <stdexcept>
#include <cstdint>

class RNG
{
public:
	RNG(const uint64_t &amount, const uint64_t &min, const uint64_t &max)
		: m_floor(min)
		, m_ceiling(max)
		, m_lastInt(min)
		, m_numLeft(amount)
		, m_generator((std::random_device())())
	{
	}

	bool HasNext() const
	{
		return m_numLeft > 0;
	}

	uint64_t NextInt()
	{
		if (m_numLeft > 0)
		{
			// Partition the range of numbers to generate from
			uint64_t rangeSize = (m_ceiling - m_lastInt) / m_numLeft;

			// Initialize random generator
			std::uniform_int_distribution<uint64_t> rg(m_floor, rangeSize);

			// Generate random number
			uint64_t randomNumber = rg(m_generator) + m_lastInt + 1;

			// Set m_lastInt to randomNumber so that randomNumber is not generated again
			m_lastInt = randomNumber;
			m_numLeft--;
			return randomNumber;
		}
		else
		{
			throw std::out_of_range("Exceeded amount of random numbers to generate.");
		}
	}
private:
	uint64_t m_floor;
	uint64_t m_ceiling;
	uint64_t m_lastInt;
	uint64_t m_numLeft;
	std::mt19937_64 m_generator;
};