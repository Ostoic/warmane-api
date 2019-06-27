#pragma once

#include <string>

#include "json.hpp"

namespace warmane::armory
{
	class profession : public armory::json_parseable
	{
		using base = armory::json_parseable;

	public:
		profession() = default;

		explicit profession(armory::json&& json);

		std::string name() const;

		unsigned int level() const;
	};

	inline profession::profession(armory::json&& json)
		: base(std::move(json))
	{
		this->expect_key("name");
		this->expect_key("level");
	}

	inline std::string profession::name() const
	{
		const auto obj = json_["name"];
		if (obj.is_null() || !obj.is_string())
			return {};

		return obj.get<std::string>();
	}

	inline unsigned int profession::level() const
	{
		const auto obj = json_["level"];
		if (obj.is_null() || !obj.is_string())
			return {};

		return static_cast<unsigned int>(
			std::stoi(obj.get<std::string>())
		);
	}
}