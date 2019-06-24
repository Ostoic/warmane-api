#pragma once

#include <string>

#include "api/error.hpp"
#include "json_parseable.hpp"

namespace warmane::armory
{
	class item : public json_parseable
	{
		using base = json_parseable;

	public:
		item() = default;

		explicit item(api::json&& json);

		std::string name() const;

		unsigned int id() const;

		unsigned int transmog_id() const;
	};

	inline item::item(api::json&& json)
		: base(std::move(json))
	{
		if (!json_.is_object())
			throw api::unmatched_json_type{"[armory::item] Expected object"};

		this->expect_key("name");
		this->expect_key("item");
	}

	inline std::string item::name() const
	{
		const auto obj = json_["name"];

		if (obj.is_null() || !obj.is_string())
			return {};

		return std::string{obj};
	}

	inline unsigned int item::id() const
	{
		const auto obj = json_["item"];

		if (obj.is_null() || !obj.is_string())
			return {};

		return static_cast<unsigned int>(
			std::stoi(std::string{obj})
		);
	}

	inline unsigned int item::transmog_id() const
	{
		const auto obj = json_["transmog"];

		if (obj.is_null() || !obj.is_string())
			return {};

		return static_cast<unsigned int>(
			std::stoi(std::string{obj})
		);
	}
}