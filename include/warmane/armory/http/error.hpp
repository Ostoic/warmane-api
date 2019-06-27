#pragma once

#include <stdexcept>

namespace warmane::armory::http
{
	class http_error : public std::runtime_error
	{
	public:
		explicit http_error(const std::string& message)
			: std::runtime_error(message.c_str())
		{}

		explicit http_error(const char* message)
			: std::runtime_error(message)
		{}
	};

	class connection_closed : public http_error
	{
	public:
		explicit connection_closed(const std::string& message = "Connection closed")
			: http_error(message.c_str())
		{}

		explicit connection_closed(const char* message)
			: http_error(message)
		{}
	};

	class unexcpected_content_type : public http_error
	{
	public:
		explicit unexcpected_content_type(const std::string& message = "Unexcepted content type")
			: http_error(message.c_str())
		{}

		explicit unexcpected_content_type(const char* message)
			: http_error(message)
		{}
	};
}