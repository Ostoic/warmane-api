#pragma once

#include <boost/regex.hpp>

#include "symbol.hpp"

namespace warmane::armory::site::parser
{
	class token
	{
	public:
		token(token&& other) noexcept;
		token(const token& other) noexcept;

		token& operator=(const token& other) noexcept;
		token& operator=(token&& other) noexcept;

		explicit token(const symbol s, const boost::smatch& match);
		explicit token(const symbol s, const std::ptrdiff_t position);

		symbol symbol() const noexcept { return symbol_; }
		std::ptrdiff_t position() const noexcept { return position_; }

		const char* name() const noexcept;

		virtual const std::string& operator[](const std::string& name) = 0;
		virtual std::string value() const = 0;

		bool empty() const;

	private:
		parser::symbol symbol_;
		std::ptrdiff_t position_;
	};

	token::token(token&& other) noexcept
		: symbol_{other.symbol_}
		, position_{other.position_}
	{}

	token::token(const token& other) noexcept
		: symbol_{other.symbol_}
		, position_{other.position_}
	{}

	token& token::operator=(const token& other) noexcept
	{
		symbol_ = other.symbol_;
		position_ = other.position_;
		return *this;
	}

	token& token::operator=(token&& other) noexcept
	{
		symbol_ = other.symbol_;
		position_ = other.position_;
		return *this;
	}

	token::token(const parser::symbol s, const boost::smatch& match)
		: token{s, match.position()}
	{}

	token::token(const parser::symbol s, const std::ptrdiff_t position)
		: symbol_{s}
		, position_{position}
	{}

	const char* token::name() const noexcept
	{
		using std::to_string;
		return to_string(symbol_);
	}

	bool token::empty() const
	{
		return this->value().empty();
	}
}