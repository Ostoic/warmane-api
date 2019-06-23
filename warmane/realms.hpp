#pragma once

#include <string>

namespace warmane
{
	class realm
	{
	public:
		constexpr realm(const char* name)
			: name_{name}
		{}

		constexpr const char* name() const
		{
			return name_;
		}

	private:
		const char* name_;
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
