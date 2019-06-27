#pragma once

#include "../../config.hpp"
#include <fmt/format.h>
#include <fmt/ostream.h>

#include "../http/connection.hpp"
#include "../character.hpp"
#include "../guild.hpp"
#include "error.hpp"
#include "target.hpp"

namespace warmane::armory::site
{
	namespace detail
	{
		armory::character parse_character(const std::string& data, const site::target& target);

		armory::guild parse_guild(const std::string& data, const site::target& target);
	}

	template <class T>
	T load(http::connection& connection, const site::target& target)
	{
		if (!connection.connected())
			throw http::connection_closed{"[armory::site::load] connection to armory was closed"};

		const auto response = connection.get(target);
		const auto content_type = response[boost::beast::http::field::content_type];

		if (content_type != "text/html")
			throw http::unexcpected_content_type{fmt::format(
				"[armory::site::load] Unexpected content type: {} (should be text/html)",
				content_type
			)};

		if constexpr (std::is_same_v<T, armory::character>)
			return detail::parse_character(response.body(), target);
		else
			return detail::parse_character(response.body(), target);
	}

	namespace detail
	{
		armory::character parse_character(const std::string& data, const site::target& target)
		{
			auto obj = json::parse(data);

			const auto error = obj["error"];
			if (!error.is_null())
			{
				const auto message = error.get<std::string>();

				if (message == "Character does not exist.")
					throw site::no_such_character{"[armory::site::load<character>] Character does not exist"};
			}

			return character{std::move(obj)};
		}

		armory::guild parse_guild(const std::string& data, const site::target& target)
		{
			auto json = armory::json::parse(data);

			const auto error = json["error"];
			if (!error.is_null())
			{
				const auto message = error.get<std::string>();
				if (message == "Guild does not exist.")
					throw site::no_such_guild{"[armory::site::load<guild>] Guild does not exist"};
			}

			return armory::guild{std::move(json)};
		}
	}
}