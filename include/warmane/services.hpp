#pragma once

#include "character.hpp"

namespace warmane
{
	constexpr std::string_view hostname()
	{ return "http://armory.warmane.com"; }


	class service
	{
	public:
		constexpr service(const char* name)
			: name_{name}
		{}

		constexpr const char* name() const
		{
			return name_;
		}

	private:
		const char* name_;
	};

	namespace services
	{
		constexpr auto character = service{"character"};
		constexpr auto guild = service{"guild"};
	}
}