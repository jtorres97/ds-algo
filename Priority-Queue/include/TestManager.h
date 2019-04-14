#pragma once

#include "Test.h"

class TestManager
{
public:
	TestManager() = default;

	bool Run()
	{
		m_test.Use();
		return true;
	}

	bool RunningTest(const TestType &testType) const
	{
		return m_test == testType;
	}
private:
	Test m_test;
};
