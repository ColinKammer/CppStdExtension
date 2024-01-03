#pragma once
#include <iostream>
#include <cassert>

#include "CjkAssert.h"

namespace cjk
{
	void on_failed_assertion(const char* assertionMessage, const char* srcFile, unsigned srcLine)
	{
		std::cout << "Assertion failed " << assertionMessage << " in " << srcFile << ":" << srcLine << std::endl;
		assert(false);
		std::terminate();
	}

}