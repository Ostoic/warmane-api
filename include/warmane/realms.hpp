#pragma once

#include <string_view>

namespace warmane
{
	class realm
	{
	public:
		constexpr realm(const std::string_view name)
			: name_{name}
		{}

		constexpr std::string_view name() const
		{
			return name_;
		}

	private:
		const std::string_view name_;
	};

	namespace realms
	{
		constexpr auto icecrown = realm{"Icecrown"};
		constexpr auto frostwolf = realm{"Frostwolf"};
		constexpr auto blackrock = realm{"Blackrock"};
		constexpr auto lordaeron = realm{"Lordaeron"};
		constexpr auto outland = realm{"Outland"};
	}
}
