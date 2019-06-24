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

	class connection_closed : public api_error
	{
	public:
		explicit connection_closed(const std::string& message = "Connection closed")
			: api_error(message.c_str())
		{}

		explicit connection_closed(const char* message)
			: api_error(message)
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

	class database_error : public std::runtime_error
	{
	public:
		explicit database_error(const std::string& message)
			: std::runtime_error(message.c_str())
		{}

		explicit database_error(const char* message)
			: std::runtime_error(message)
		{}
	};

	class no_such_character : public database_error
	{
	public:
		explicit no_such_character(const std::string& message = "Character does not exist")
			: database_error(message.c_str())
		{}

		explicit no_such_character(const char* message)
			: database_error(message)
		{}
	};

	class no_such_guild : public database_error
	{
	public:
		explicit no_such_guild(const std::string& message = "Guild does not exist")
			: database_error(message.c_str())
		{}

		explicit no_such_guild(const char* message)
			: database_error(message)
		{}
	};
}