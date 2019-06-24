#pragma once

#include <string>

#include "api/json.hpp"

namespace warmane::armory
{
	class talent : public api::json_parseable
	{
		using base = api::json_parseable;

	public:
		talent() = default;

		explicit talent(api::json&& json);

		std::string tree() const;

		unsigned int points(unsigned int index) const;
	};

	inline talent::talent(api::json&& json)
		: base(std::move(json))
	{}

}