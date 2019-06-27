#pragma once

#include <vector>
#include <regex>
#include <memory>

#include "tokens/div.hpp"
#include "tokens/span.hpp"
#include "tokens/content.hpp"
#include "patterns/html.hpp"

#include <boost/regex.hpp>
#include <boost/range/algorithm/merge.hpp>

namespace warmane::armory::site::parser
{
	template <class Token>
	std::vector<std::unique_ptr<token>>
		extract_tokens(const std::string& text, const boost::regex& pattern)
	{
		std::vector<std::unique_ptr<token>> tokens;
		auto it = boost::sregex_iterator{text.begin(), text.end(), pattern};
		const auto end = boost::sregex_iterator{};

		for (; it != end; ++it)
		{
			if (it->size() <= 1)
				continue;

			auto token = std::make_unique<Token>(*it);
			if (!token->empty())
				tokens.push_back(std::move(token));
		}

		return tokens;
	}

	inline std::vector<std::unique_ptr<token>> lex(const std::string& text)
	{
		const auto merge = [&](auto& range1, auto& range2, auto& output)
		{
			return std::merge(
				std::make_move_iterator(range1.begin()), std::make_move_iterator(range1.end()),
				std::make_move_iterator(range2.begin()), std::make_move_iterator(range2.end()),
				std::back_inserter(output),
				[](const auto& lhs, const auto& rhs)
				{
					return lhs->position() < rhs->position();
				}
			);
		};

		std::vector<std::unique_ptr<token>> temp;
		std::vector<std::unique_ptr<token>> tokens;

		auto div_tokens = extract_tokens<tokens::div>(text, patterns::tag_div());
		auto span_tokens = extract_tokens<tokens::span>(text, patterns::tag_span());
		auto content_tokens = extract_tokens<tokens::content>(text, patterns::tag_content());

		merge(div_tokens, span_tokens, temp);
		merge(content_tokens, temp, tokens);
		return tokens;
	}
}