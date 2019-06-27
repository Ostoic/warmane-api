#pragma once

#include "html_parser.hpp"
#include "patterns.hpp"
#include "html.hpp"

#include <boost/range/algorithm/find_if.hpp>

namespace warmane::armory::site::parser
{
	namespace productions
	{
		void character_stats(html_parser& parser)
		{
			const auto& tokens = parser.tokens();

			boost::find_if(tokens, [](const token& token)
			{
				return token.symbol() == symbol::div && tag{token}["class"] == "character-stats";
			});
		}
	}
}