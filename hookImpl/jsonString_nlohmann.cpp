#pragma once
#include "JsonString.h"
#include "CjkAssert.h"

#include "nlohmann/json.hpp"

namespace cjk {

	JsonString::JsonString(const std::string& s)
		:m_value(s)
	{
		CJK_ASSERT_NOTHROW(nlohmann::json::parse(m_value), "JsonString is not actually json parsable");
	}
}