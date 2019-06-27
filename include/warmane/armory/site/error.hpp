#pragma once

#include <stdexcept>

namespace warmane::armory::site
{
	class site_error : public std::runtime_error
	{
	public:
		explicit site_error(const std::string& message)
			: std::runtime_error(message.c_str())
		{}

		explicit site_error(const char* message)
			: std::runtime_error(message)
		{}
	};


	class no_such_character : public site_error
	{
	public:
		explicit no_such_character(const std::string& message = "Character does not exist")
			: site_error(message.c_str())
		{}

		explicit no_such_character(const char* message)
			: site_error(message)
		{}
	};

	class no_such_guild : public site_error
	{
	public:
		explicit no_such_guild(const std::string& message = "Guild does not exist")
			: site_error(message.c_str())
		{}

		explicit no_such_guild(const char* message)
			: site_error(message)
		{}
	};
}