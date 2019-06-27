#include "targetver.hpp"

#include "../../include/warmane/armory/http.hpp"
#include "../../include/warmane/armory/api.hpp"
#include "../../include/warmane/armory/site.hpp"
#include "../../include/warmane/armory/character.hpp"
//#include "../../include/warmane/armory/site/parser/html_parser.hpp"
#include "../../include/warmane/armory/site/parser/lex.hpp"
//#include "../../include/warmane/armory/guild.hpp"

#include <iostream>
#include <fstream>
#include <thread>

#include <boost/range/algorithm/find_if.hpp>

#include <fmt/format.h>

namespace asio = boost::asio;
namespace armory = warmane::armory;

void test_api(armory::http::connection& connection, const std::string& name)
{
	//const auto character = armory::load_character(connection, name);

	////armory::armory::json obj;
	////std::ifstream{"act.json"} >> obj;

	////const armory::character character{std::move(obj)};

	//std::cout << "name: " << character.name() << '\n';
	//std::cout << "class: " << character.player_class() << '\n';
	//std::cout << "gender: " << character.gender() << '\n';
	//std::cout << "realm: " << character.realm() << '\n';
	//std::cout << "online: " << character.online() << '\n';
	//std::cout << "level: " << character.level() << '\n';
	//std::cout << "faction: " << character.faction() << '\n';
	//std::cout << "honorablekills: " << character.honorable_kills() << '\n';
	//std::cout << "guild1: " << character.guild() << '\n';
	//std::cout << "achievementpoints: " << character.achievement_points() << '\n';

	//const auto equipment = character.equipment();
	//const auto professions = character.professions();

	//for (const auto& item : equipment)
	//	std::cout << "item: " << item.name() << '\n';

	//for (const auto& profession : professions)
	//	std::cout << "profession: " << profession.name() << '\n';

	//std::cout << "\n";

	////std::ifstream{"carpe.json"} >> obj;
	////const armory::guild guild{std::move(obj)};

	//const auto guild = armory::load_guild(connection, character);

	//std::cout << "guild2: " << guild.name() << '\n';
	//std::cout << "realm: " << guild.realm() << '\n';

	//const auto roster = guild.roster();
	//for (const auto& character : roster)
	//{
	//	if (character.online())
	//		std::cout << character.name() << '\n';
	//}
}

int main(int argc, char* argv[])
{
	namespace chrono = std::chrono;
	namespace parser = armory::site::parser;

	try
	{
		//auto connection = armory::connect();

		std::stringstream html_stream;
		html_stream << std::ifstream{"profile.html"}.rdbuf();

		const std::string html = html_stream.str();

		//const auto parser = parser::html_parser{
		//	parser::patterns::talent1(),
		//	parser::patterns::talent2(),
		//};

		const auto start = chrono::steady_clock::now();
		const auto tokens = parser::lex(html);
		const auto stop = chrono::steady_clock::now();

		fmt::print("Took {} milliseconds to lex\n",
			chrono::duration_cast<chrono::milliseconds>(stop - start).count()
		);

		//boost::find_if(tokens, [](const std::unique_ptr<parser::token>& token)
		//{
			//return token->
		//});

		//const auto& it = boost::range::find_if(tokens, [](const auto& token)
		//{
		//	return token.symbol() == parser::symbol::div;
		//});

		//const auto character
		//	= armory::api::load<armory::character>(connection, "Act");

		//const auto character2
			//= armory::site::load<armory::character>(connection, "Act");

		//std::cout << "hks: " << character.honorable_kills() << "\n\n";
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
	catch (armory::json_error& e)
	{
		std::cout << e.what() << '\n';
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}

	return 0;
}
