#pragma once

#include <nlohmann/json.hpp>

#include "error.hpp"

namespace warmane::armory
{
	using json = nlohmann::json;

	class json_parseable
	{
	public:
		json_parseable() = default;

		explicit json_parseable(armory::json&& json);

		const armory::json& json() const;
		armory::json& json();

		template <class Key, class Value>
		void insert(const Key& key, const Value& value);

	protected:
		void expect_key(const std::string& key) const;

	protected:
		armory::json json_;
	};

	inline void to_json(armory::json& j, const json_parseable& p)
	{
		j = p.json();
	}

	inline void from_json(const armory::json& j, json_parseable& p)
	{
		p.json() = j;
	}

	inline void json_parseable::expect_key(const std::string& key) const
	{
		if (json_[key].is_null())
			throw expected_json_key("[armory::item] Expected key: " + key);
	}

	inline json_parseable::json_parseable(armory::json&& json)
		: json_(std::move(json))
	{}

	const json& json_parseable::json() const
	{ return json_; }

	json& json_parseable::json()
	{ return json_; }

	template <class Key, class Value>
	inline void json_parseable::insert(const Key& key, const Value& value)
	{
		json_[key] = value;
	}
}