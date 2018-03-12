#pragma once
#include <stdio.h>
#include <sstream>

class DummyClass
{
public:
	DummyClass() : m_i(0)
	{
	}
	void printMe()
	{
		++m_i;
		std::ostringstream os;
		os << "DummyClass called ";
		os << m_i;
		os << " times\n";
		std::string s(os.str());
		printf(s.c_str());
	}
private:
	unsigned int m_i;
};