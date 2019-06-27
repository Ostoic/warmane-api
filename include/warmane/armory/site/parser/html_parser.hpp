#pragma once

#include "../../../config.hpp"
#include <fmt/format.h>
#include <fmt/ostream.h>

#include <boost/regex.hpp>
#include <vector>

#include "token.hpp"
#include "error.hpp"

#include "../../json.hpp"

namespace warmane::armory::site::parser
{
	class html_parser
	{
	public:
		using iterator = std::vector<token>::iterator;
		using const_iterator = std::vector<token>::const_iterator;

	public:
		html_parser() = default;
		explicit html_parser(const std::vector<token>& tokens);
		explicit html_parser(std::vector<token>&& tokens);

		symbol peek() const;

		void expect(symbol s) const;

		const token& next_token();

		const std::vector<token>& tokens() const noexcept;

	private:
		//void find_

	private:
		std::vector<token> tokens_;
		iterator it_;
		//std::unordered_map<std::string, >
			//data_finder_;
	};

	inline void to_json(armory::json& j, const html_parser& p)
	{

	}

	inline void from_json(const armory::json& j, html_parser& p)
	{

	}

	inline html_parser::html_parser(const std::vector<token>& tokens)
		: tokens_{tokens}
		, it_{std::begin(tokens_)}
	{}

	inline html_parser::html_parser(std::vector<token>&& tokens)
		: tokens_{std::move(tokens)}
		, it_{std::begin(tokens_)}
	{}

	inline symbol html_parser::peek() const
	{
		return it_->symbol();
	}

	inline void html_parser::expect(const symbol s) const
	{
		const symbol peeked = this->peek();
		if (peeked != s)
			throw unexpected_token{
				fmt::format("[html_parser::expect] Expected token:{}, but got token:{}",
					s, peeked
				)
			};
	}

	inline const token& html_parser::next_token()
	{
		return *(it_++);
	}

	inline const std::vector<token>& html_parser::tokens() const noexcept
	{
		return tokens_;
	}
}