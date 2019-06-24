#pragma once

#include <string_view>

namespace warmane::armory
{
	constexpr const char* hostname = "armory.warmane.com";

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