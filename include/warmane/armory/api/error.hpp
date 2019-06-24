#pragma once

#include <system_error>

namespace warmane::armory::api
{
	class connection_closed : public std::runtime_error
	{
	public:
		explicit connection_closed(const std::string& message = "Connection closed")
			: std::runtime_error(message.c_str())
		{}

		explicit connection_closed(const char* message)
			: std::runtime_error(message)
		{}
	};

	class too_many_requests : public std::runtime_error
	{
	public:
		explicit too_many_requests(const std::string& message = "Too many requests")
			: std::runtime_error(message.c_str())
		{}

		explicit too_many_requests(const char* message)
			: std::runtime_error(message)
		{}
	};

	class unmatched_json_type : public std::runtime_error
	{
	public:
		explicit unmatched_json_type(const std::string& message)
			: std::runtime_error(message.c_str())
		{}

		explicit unmatched_json_type(const char* message)
			: std::runtime_error(message)
		{}
	};

	class expected_json_key : public std::runtime_error
	{
	public:
		explicit expected_json_key(const std::string& message)
			: std::runtime_error(message.c_str())
		{}

		explicit expected_json_key(const char* message)
			: std::runtime_error(message)
		{}
	};

	//	class unexpected_content_type : boost::system
	//	{
	//	public:
	//	};
	//}
}