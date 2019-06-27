#pragma once

#include <stdexcept>

namespace warmane::armory::site::parser
{
	class parser_error : public std::runtime_error
	{
	public:
		explicit parser_error(const std::string& message)
			: std::runtime_error(message.c_str())
		{}

		explicit parser_error(const char* message)
			: std::runtime_error(message)
		{}
	};

	class unexpected_token : public parser_error
	{
	public:
		explicit unexpected_token(const std::string& message = "Unexpected token")
			: parser_error(message.c_str())
		{}

		explicit unexpected_token(const char* message)
			: parser_error(message)
		{}
	};
}