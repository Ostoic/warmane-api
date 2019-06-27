#pragma once

#include "http/connection.hpp"

#include "json.hpp"
#include "character.hpp"
#include "../realms.hpp"

namespace warmane::armory
{
	class guild : public armory::json_parseable
	{
		using base = armory::json_parseable;
	public:
		guild() = default;

		explicit guild(armory::json&& json);

		std::string name() const;
		std::string realm() const;

		std::vector<character> roster() const;
	};

	inline guild::guild(armory::json&& json)
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
}