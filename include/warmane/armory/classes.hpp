#pragma once

#include <string_view>

namespace warmane::armory
{
	struct player_class
	{
		const char* name;
	};

	namespace classes
	{
		constexpr auto warrior = player_class{"warrior"};
		constexpr auto rogue = player_class{"rogue"};
		constexpr auto warlock = player_class{"warlock"};
		constexpr auto mage = player_class{"mage"};
		constexpr auto druid = player_class{"druid"};
		constexpr auto paladin = player_class{"paladin"};
		constexpr auto hunter = player_class{"hunter"};
		constexpr auto priest = player_class{"priest"};
		constexpr auto death_knight = player_class{"death_knight"};
	}
}