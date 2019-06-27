#pragma once

#include <string>

#include "json.hpp"

namespace warmane::armory
{
	class talent : public armory::json_parseable
	{
		using base = armory::json_parseable;

	public:
		talent() = default;

		explicit talent(armory::json&& json);

		std::string tree() const;

		unsigned int points(unsigned int index) const;
	};

	inline talent::talent(armory::json&& json)
		: base(std::move(json))
	{}

}