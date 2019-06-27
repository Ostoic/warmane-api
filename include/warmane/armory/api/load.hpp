#pragma once

#include "../../config.hpp"

#include <fmt/format.h>
#include <fmt/ostream.h>

#include "../http/connection.hpp"
#include "../character.hpp"
#include "../guild.hpp"

#include "target.hpp"
#include "error.hpp"

namespace warmane::armory::api
{
	namespace detail
	{
		template <class Data>
		armory::character parse_character(const Data& data, const api::target& target);

		template <class Data>
		armory::guild parse_guild(const Data& data, const api::target& target);
	}

	template <class T>
	T load(http::connection& connection, const api::target& target)
	{
		if (!connection.connected())
			throw http::connection_closed{"[armory::api::load] connection to armory was closed"};

		const auto response = connection.get(target);
		const auto content_type = response[boost::beast::http::field::content_type];

		if (content_type != "application/json")
			throw http::unexcpected_content_type{fmt::format(
				"[armory::api::load] Unexpected content type: {} (should be application/json)",
				content_type
			)};

		if constexpr (std::is_same_v<T, armory::character>)
			return detail::parse_character(response.body(), target);
		else
			return detail::parse_character(response.body(), target);
	}

	namespace detail
	{
		template <class Data>
		armory::character parse_character(const Data& data, const api::target& target)
		{
			auto json = armory::json::parse(data);

			const auto error = json["error"];
			if (!error.is_null())
			{
				const auto message = error.get<std::string>();
				if (message == "Too many requests.")
					throw api::too_many_requests{
						"[armory::api::load<character>] API responded with too many requests, try again later"
					};

				else if (message == "Character does not exist.")
					throw api::no_such_character{"[armory::api::load<character>] Character does not exist"};
			}

			return character{std::move(json)};
		}

		template <class Data>
		armory::guild parse_guild(const Data& data, const api::target& target)
		{
			auto json = armory::json::parse(data);

			const auto error = json["error"];
			if (!error.is_null())
			{
				const auto message = error.get<std::string>();
				if (message == "Too many requests.")
					throw api::too_many_requests{
						"[armory::api::load<guild>] API responded with too many requests, try again later"
					};

				else if (message == "Guild does not exist.")
					throw api::no_such_guild{"[armory::api::load<guild>] Guild does not exist"};
			}

			return armory::guild{std::move(json)};
		}
	}
}