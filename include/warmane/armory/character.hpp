#pragma once

#include <nlohmann/json.hpp>

#include "api/connection.hpp"
#include "api/target.hpp"
#include "api/error.hpp"

#include "json_parseable.hpp"
#include "item.hpp"
#include "talent.hpp"
#include "profession.hpp"

namespace warmane::armory
{
	class character : public json_parseable
	{
		using base = json_parseable;
	public:
		enum class info_type { partial, summary };

	public:
		character() = default;

		explicit character(api::json&& json, info_type type = info_type::summary);

		std::string name() const;
		std::string realm() const;

		bool online() const;

		unsigned int level() const;

		std::string faction() const;
		std::string gender() const;

		std::string race() const;
		std::string player_class() const;

		unsigned int honorable_kills() const;

		std::string guild() const;

		unsigned int achievement_points() const;

		std::vector<item> equipment() const;
		std::vector<talent> talents() const;
		std::vector<profession> professions() const;

		bool is_partial() const;

	private:
		const info_type info_type_;
	};

	inline character::character(api::json&& obj, info_type t)
		: base(std::move(obj))
		, info_type_{t}
	{
		this->expect_key("name");
		this->expect_key("level");
		this->expect_key("gender");
		this->expect_key("race");
		this->expect_key("class");
	}

	inline std::string character::name() const
	{
		const auto obj = json_["name"];
		if (obj.is_null() || !obj.is_string())
			return {};

		return obj.get<std::string>();
	}

	inline std::string character::realm() const
	{
		const auto obj = json_["realm"];
		if (obj.is_null() || !obj.is_string())
			return {};

		return obj.get<std::string>();
	}

	inline bool character::online() const
	{
		const auto obj = json_["online"];
		if (obj.is_null() || !obj.is_boolean())
			return {};

		return obj.get<bool>();
	}

	inline unsigned int character::level() const
	{
		const auto obj = json_["level"];
		if (obj.is_null() || !obj.is_string())
			return {};

		return static_cast<unsigned int>(
			std::stoi(obj.get<std::string>())
		);
	}

	inline std::string character::faction() const
	{
		const auto obj = json_["faction"];
		if (obj.is_null() || !obj.is_string())
			return {};

		return obj.get<std::string>();
	}

	inline std::string character::gender() const
	{
		const auto obj = json_["gender"];
		if (obj.is_null() || !obj.is_string())
			return {};

		return obj.get<std::string>();
	}

	inline std::string character::race() const
	{
		const auto obj = json_["faction"];
		if (obj.is_null() || !obj.is_string())
			return {};

		return obj.get<std::string>();
	}

	inline std::string character::player_class() const
	{
		const auto obj = json_["class"];
		if (obj.is_null() || !obj.is_string())
			return {};

		return obj.get<std::string>();
	}

	inline unsigned int character::honorable_kills() const
	{
		const auto obj = json_["honorablekills"];
		if (obj.is_null() || !obj.is_string())
			return {};

		return static_cast<unsigned int>(
			std::stoi(obj.get<std::string>())
		);
	}

	inline std::string character::guild() const
	{
		const auto obj = json_["guild"];
		if (obj.is_null() || !obj.is_string())
			return {};

		return obj.get<std::string>();
	}

	inline unsigned int character::achievement_points() const
	{
		const auto obj = json_["achievementpoints"];
		if (obj.is_null() || !obj.is_string())
			return {};

		return static_cast<unsigned int>(
			std::stoi(obj.get<std::string>())
		);
	}

	inline std::vector<item> character::equipment() const
	{
		const auto obj = json_["equipment"];

		if (obj.is_null() || !obj.is_array())
			return {};

		return obj.get<std::vector<item>>();
	}

	inline std::vector<profession> character::professions() const
	{
		const auto obj = json_["professions"];

		if (obj.is_null() || !obj.is_array())
			return {};

		return obj.get<std::vector<profession>>();
	}

	inline bool character::is_partial() const
	{
		return info_type_ == info_type::partial;
	}

	inline character load_character(
		api::connection& connection,
		const std::string& character_name,
		warmane::realm realm = realms::icecrown
	)
	{
		if (!connection.connected())
			throw api::connection_closed{"[armory::load_character] invalid API connection"};

		auto json = api::json::parse(
			connection.get(
				api::target{character_name, services::character, realm}
			).body()
		);

		const auto error = json["error"];
		if (!error.is_null() && error.get<std::string>() == "Too many requests.")
			throw api::too_many_requests{"[armory::load_character] API responded with too many requests, try again later"};

		return character{std::move(json)};
	}
}
