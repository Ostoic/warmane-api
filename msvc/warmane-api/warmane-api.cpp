#include "targetver.hpp"

#include "../../include/warmane/armory/api.hpp"
#include "../../include/warmane/armory/character.hpp"
#include "../../include/warmane/armory/guild.hpp"
#include "../../include/warmane/armory/api/json.hpp"

#include <iostream>
#include <fstream>
#include <thread>

namespace http = boost::beast::http;
namespace asio = boost::asio;
namespace armory = warmane::armory;

void test_character(armory::api::connection& api, const std::string& name)
{
}

int main(int argc, char* argv[])
{

	try
	{
		auto api = armory::api::connect();
		const auto character = armory::load_character(api, "Act");
		
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
		std::cout << "guild1: " << character.guild() << '\n';
		std::cout << "achievementpoints: " << character.achievement_points() << '\n';

		const auto equipment = character.equipment();
		const auto professions = character.professions();

		for (const auto& item : equipment)
			std::cout << "item: " << item.name() << '\n';

		for (const auto& profession : professions)
			std::cout << "profession: " << profession.name() << '\n';

		std::cout << "\n";

		//std::ifstream{"carpe.json"} >> obj;
		//const armory::guild guild{std::move(obj)};
		
		const auto guild = armory::load_guild(api, character);

		std::cout << "guild2: " << guild.name() << '\n';
		std::cout << "realm: " << guild.realm() << '\n';

		const auto roster = guild.roster();
		for (const auto& character : roster)
		{
			if (character.online())
				std::cout << character.name() << '\n';
		}
	}
	catch (boost::system::system_error& e)
	{
		if (e.code() == asio::error::host_not_found)
			std::cout << "Unable to resolve hostname: " << armory::hostname << '\n';
		else
			std::cout << "Error: " << e.what() << '\n';
	}
	catch (armory::api::api_error& e)
	{
		std::cout << e.what() << '\n';
	}
	catch (armory::api::json_error& e)
	{
		std::cout << e.what() << '\n';
	}
	catch (armory::api::database_error& e)
	{
		std::cout << e.what() << '\n';
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}

	return 0;
}
