#pragma once

#include <string_view>

namespace warmane::armory
{
	constexpr std::string_view hostname = "armory.warmane.com";

	class service
	{
	public:
		constexpr service(const std::string_view name)
			: name_{name}
		{}

		constexpr std::string_view name() const
		{
			return name_;
		}

	private:
		const std::string_view name_;
	};

	namespace services
	{
		constexpr auto character = service{"character"};
		constexpr auto guild = service{"guild"};
	}
}