#pragma once

#include <string>

#include "json_parseable.hpp"

namespace warmane::armory
{
	class talent : public json_parseable
	{
		using base = json_parseable;

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