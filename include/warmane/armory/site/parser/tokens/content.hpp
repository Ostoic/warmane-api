#pragma once

#include "../token.hpp"
#include "../html/tag.hpp"

#include <string>
#include <boost/regex.hpp>
#include <boost/algorithm/string/trim_all.hpp>

namespace warmane::armory::site::parser::tokens
{
	class content : public token
	{
	public:
		static constexpr const char* name = "content";
		static constexpr auto symbol = symbol::content;

	public:
		explicit content(const boost::smatch& match);

		const std::string& operator[](const std::string& name) override;
		std::string value() const override;

	private:
		std::string text_;
	};

	inline content::content(const boost::smatch& match)
		: token{content::symbol, match.position()}
		, text_{[&]
		{
			std::string text{match[1]};
			boost::trim_all(text);
			return text;
		}()}
	{}

	const std::string& content::operator[](const std::string& name)
	{
		return text_;
	}

	std::string content::value() const
	{
		return text_;
	}
}
