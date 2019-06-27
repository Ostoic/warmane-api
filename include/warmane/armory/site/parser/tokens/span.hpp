#pragma once

#include "../token.hpp"
#include "../html/tag.hpp"

#include <boost/algorithm/string/trim_all.hpp>

namespace warmane::armory::site::parser::tokens
{
	class span : public token
	{
	public:
		static constexpr const char* name = "span";
		static constexpr auto symbol = symbol::span;

	public:
		explicit span(const boost::smatch& match);

		const std::string& operator[](const std::string& name) override;
		std::string value() const override;

	private:
		html::tag tag_;
	};

	inline span::span(const boost::smatch& match)
		: token{span::symbol, match.position()}
		, tag_{html::to_tag(span::name, match)}
	{}

	const std::string& span::operator[](const std::string& name)
	{
		return tag_[name];
	}

	std::string span::value() const
	{
		using std::to_string;
		return span::name;
	}
}
