#pragma once

#include <chrono>
#include <thread>
#include <vector>

#include "Utils.h"

enum TestType
{
	INSERTION,
	REMOVE,
	SEARCH
};

class Test
{
public:
	Test()
		: m_start(std::chrono::system_clock::now())
		, m_end(std::chrono::system_clock::now())
		, m_minInterval(50.0)
		, m_maxInterval(500.0)
		, m_isReady(true)
		, m_testType()
	{
		// Initialize the cooldown
		m_cooldown = COSC::Rand(m_minInterval, m_maxInterval);

		// Container for enum values
		m_testTypes = { INSERTION, REMOVE, SEARCH };
	}

	void Use()
    {
        if (!m_isReady)
        {
            return;
        }

		// Get a random operation to perform
		m_testType = m_testTypes[COSC::Rand(0, 2)];

		// Variable cool downs for each test type
        switch (m_testType) 
		{
        	case INSERTION:
				m_cooldown = COSC::Rand(m_minInterval - 50.0, (m_maxInterval / 2.f) - 50.0);
        		break;
			case REMOVE:
				m_cooldown = COSC::Rand(m_minInterval + 300.0, m_maxInterval);
        		break;
			case SEARCH:
				m_cooldown = COSC::Rand(m_minInterval + 230.0, m_maxInterval - 100.0);
        		break;
        }
        ApplyCooldown();
    }
private:
    void ApplyCooldown()
    {
        using namespace std::chrono;
		m_start = system_clock::now();
        m_isReady = false;

		std::thread t([this]()
        {

            while (!m_isReady)
            {
				m_end = system_clock::now();
				duration<double, std::milli> elapsed = m_end - m_start;
				m_isReady = elapsed.count() >= m_cooldown;
            }
        });
        t.join();
    }

	std::chrono::time_point<std::chrono::system_clock> m_start;
	std::chrono::time_point<std::chrono::system_clock> m_end;
    double m_cooldown;
	double m_minInterval;
	double m_maxInterval;
    bool m_isReady;
	TestType m_testType;
	std::vector<TestType> m_testTypes;

	friend bool operator==(const Test &rhs, const TestType &lhs)
	{
		return rhs.m_testType == lhs;
	}
};

