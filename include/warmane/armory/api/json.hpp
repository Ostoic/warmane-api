#pragma once

#include <nlohmann/json.hpp>

namespace warmane::armory::api
{
	using json = nlohmann::json;

	class json_parseable
	{
	public:
		json_parseable() = default;

		explicit json_parseable(api::json&& json);

		const api::json& json() const;
		api::json& json();

	protected:
		void expect_key(const std::string& key) const;

	protected:
		api::json json_;
	};

	inline void to_json(api::json& j, const json_parseable& p)
	{
		j = p.json();
	}

	inline void from_json(const api::json& j, json_parseable& p)
	{
		p.json() = j;
	}

	inline void json_parseable::expect_key(const std::string& key) const
	{
		if (json_[key].is_null())
			throw api::expected_json_key("[armory::item] Expected key: " + key);
	}

	inline json_parseable::json_parseable(api::json&& json)
		: json_(std::move(json))
	{}

	const api::json& json_parseable::json() const
	{ return json_; }

	api::json& json_parseable::json()
	{ return json_; }
}