#pragma once
#include <string>

namespace cjk {

	class JsonString {
		std::string m_value;

	public:
		//constructor will check json parseablity depending on Assertion settings
		JsonString(const std::string&);

		operator const std::string& () const {
			return m_value;
		}

	};
}