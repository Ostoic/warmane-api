#include "targetver.hpp"

#include "../../include/warmane/armory/api.hpp"
#include "../../include/warmane/armory/character.hpp"
#include "../../include/warmane/armory/guild.hpp"
#include "../../include/warmane/armory/api/json.hpp"

#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
	namespace http = boost::beast::http;
	namespace asio = boost::asio;
	namespace armory = warmane::armory;

	try
	{
		auto api = armory::api::connect();
		const auto character = armory::load_character(api, "Adidi");
		//const auto guild = armory::load_guild(api, character);
		//armory::api::json obj;
		//std::ifstream{"act.json"} >> obj;

		//const armory::character character{std::move(obj)};

		std::cout << "name: " << character.name() << '\n';
		std::cout << "class: " << character.player_class() << '\n';
		std::cout << "gender: " << character.gender() << '\n';
		std::cout << "realm: " << character.realm() << '\n';
		std::cout << "online: " << character.online() << '\n';
		std::cout << "level: " << character.level() << '\n';
		std::cout << "faction: " << character.faction() << '\n';
		std::cout << "honorablekills: " << character.honorable_kills() << '\n';
		std::cout << "guild: " << character.guild() << '\n';
		std::cout << "achievementpoints: " << character.achievement_points() << '\n';

		const auto equipment = character.equipment();
		const auto professions = character.professions();

		for (const auto& item : equipment)
			std::cout << "item: " << item.name() << '\n';

		for (const auto& profession : professions)
			std::cout << "profession: " << profession.name() << '\n';
	}
	catch (boost::system::system_error& e)
	{
		if (e.code() == asio::error::host_not_found)
			std::cout << "Unable to resolve hostname: " << armory::hostname << '\n';
		else
			std::cout << "Error: " << e.what() << '\n';
	}
	catch (armory::api::too_many_requests& e)
	{
		std::cout << e.what() << '\n';
	}
	catch (armory::api::connection_closed& e)
	{
		std::cout << e.what() << '\n';
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}

	return 0;
}
