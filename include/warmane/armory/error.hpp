#pragma once

#include <stdexcept>

namespace warmane::armory
{
	class json_error : public std::runtime_error
	{
	public:
		explicit json_error(const std::string& message)
			: std::runtime_error(message.c_str())
		{}

		explicit json_error(const char* message)
			: std::runtime_error(message)
		{}
	};

	class unmatched_json_type : public json_error
	{
	public:
		explicit unmatched_json_type(const std::string& message)
			: json_error(message.c_str())
		{}

		explicit unmatched_json_type(const char* message)
			: json_error(message)
		{}
	};

	class expected_json_key : public json_error
	{
	public:
		explicit expected_json_key(const std::string& message)
			: json_error(message.c_str())
		{}

		explicit expected_json_key(const char* message)
			: json_error(message)
		{}
	};
}