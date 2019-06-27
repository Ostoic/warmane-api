#pragma once

#include <system_error>

namespace warmane::armory::api
{
	class api_error : public std::runtime_error
	{
	public:
		explicit api_error(const std::string& message)
			: std::runtime_error(message.c_str())
		{}

		explicit api_error(const char* message)
			: std::runtime_error(message)
		{}
	};

	class too_many_requests : public api_error
	{
	public:
		explicit too_many_requests(const std::string& message = "Too many requests")
			: api_error(message.c_str())
		{}

		explicit too_many_requests(const char* message)
			: api_error(message)
		{}
	};

	class no_such_character : public api_error
	{
	public:
		explicit no_such_character(const std::string& message = "Character does not exist")
			: api_error(message.c_str())
		{}

		explicit no_such_character(const char* message)
			: api_error(message)
		{}
	};

	class no_such_guild : public api_error
	{
	public:
		explicit no_such_guild(const std::string& message = "Guild does not exist")
			: api_error(message.c_str())
		{}

		explicit no_such_guild(const char* message)
			: api_error(message)
		{}
	};
}