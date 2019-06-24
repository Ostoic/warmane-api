#pragma once

#include "api/connection.hpp"
#include "api/target.hpp"
#include "api/error.hpp"
#include "api/json.hpp"

#include "character.hpp"
#include "../realms.hpp"

namespace warmane::armory
{
	class guild : public api::json_parseable
	{
		using base = api::json_parseable;
	public:
		guild() = default;

		explicit guild(api::json&& json);

		std::string name() const;
		std::string realm() const;

		std::vector<character> roster() const;
	};

	inline guild::guild(api::json&& json)
		: base(std::move(json))
	{}

	inline std::string guild::name() const
	{
		const auto obj = json_["name"];
		if (obj.is_null() || !obj.is_string())
			return {};

		return obj.get<std::string>();
	}

	inline std::string guild::realm() const
	{
		const auto obj = json_["realm"];
		if (obj.is_null() || !obj.is_string())
			return {};

		return obj.get<std::string>();
	}

	inline std::vector<character> guild::roster() const
	{
		const auto obj = json_["roster"];
		if (obj.is_null() || !obj.is_array())
			return {};

		return obj.get<std::vector<character>>();
	}

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
		if (!error.is_null())
		{
			const auto message = error.get<std::string>();
			if (message == "Too many requests.")
				throw api::too_many_requests{"[armory::load_guild] API responded with too many requests, try again later"};

			else if (message == "Guild does not exist.")
				throw api::no_such_guild{"[armory::load_guild] Guild does not exist"};
		}

		return guild{std::move(json)};
	}

	guild load_guild(api::connection& connection, const character& character)
	{
		return load_guild(connection, character.guild(), warmane::realm{character.realm().c_str()});
	}
}