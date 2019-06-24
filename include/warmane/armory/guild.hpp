#pragma once

#include "api/connection.hpp"
#include "api/target.hpp"
#include "api/error.hpp"

#include "json_parseable.hpp"
#include "character.hpp"
#include "../realms.hpp"

namespace warmane::armory
{
	class guild : public json_parseable
	{
		using base = json_parseable;
	public:
		guild() = default;

		explicit guild(api::json&& json);
	};

	inline guild::guild(api::json&& json)
		: base(std::move(json))
	{}

	guild load_guild(
		api::connection& connection,
		const std::string& guild_name,
		warmane::realm realm = realms::icecrown
	)
	{
		if (!connection.connected())
			throw api::connection_closed{"[armory::load_guild] invalid API connection"};

		auto json = api::json::parse(
			connection.get(
				api::target{guild_name, services::guild, realm}
			).body()
		);

		const auto error = json["error"];
		if (!error.is_null() && error.get<std::string>() == "Too many requests.")
			throw api::too_many_requests{"[armory::load_guild] API responded with too many requests, try again later"};

		return guild{std::move(json)};
	}

	guild load_guild(api::connection& connection, const character& character)
	{
		return load_guild(connection, character.name(), warmane::realm{character.realm()});
	}
}