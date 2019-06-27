#pragma once

#include "../token.hpp"
#include "../html/tag.hpp"

#include <boost/algorithm/string/trim_all.hpp>

namespace warmane::armory::site::parser::tokens
{
	class div : public token
	{
	public:
		static constexpr const char* name = "div";
		static constexpr auto symbol = symbol::div;

	public:
		explicit div(const boost::smatch& match);

		const std::string& operator[](const std::string& name) override;
		std::string value() const override;

	private:
		html::tag tag_;
	};

	inline div::div(const boost::smatch& match)
		: token{div::symbol, match.position()}
		, tag_{html::to_tag(div::name, match)}
	{}

	const std::string& div::operator[](const std::string& name)
	{ return tag_[name]; }

	std::string div::value() const
	{
		using std::to_string;
		return div::name;
	}
}
