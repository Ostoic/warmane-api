#pragma once

#include "../../../../config.hpp"
#include <fmt/format.h>
#include <fmt/ostream.h>

#include <boost/range/algorithm/find_if.hpp>
#include <vector>

#include "../patterns/html.hpp"
#include "../error.hpp"

#include "attribute.hpp"

namespace warmane::armory::site::parser::html
{
//interface:
	class tag
	{
	public:
		explicit tag(std::string&& name, std::vector<attribute>&& attributes) noexcept;

		tag(tag&& other) noexcept;

		const std::string& operator[](const std::string& name);

		bool has_attribute(const std::string& name) const;

	private:
		std::string name_;
		std::vector<attribute> attributes_;
	};

	tag to_tag(std::string tag_name, const boost::smatch& tag_match);

//impl:
	inline tag::tag(std::string&& name, std::vector<attribute>&& attributes) noexcept
		: name_{std::move(name)}
		, attributes_{std::move(attributes)}
	{}

	inline tag::tag(tag&& other) noexcept
		: attributes_{std::move(other.attributes_)}
	{}

	inline const std::string& tag::operator[](const std::string& name)
	{
		const auto it = boost::find_if(attributes_, [&](const attribute& attribute)
		{
			return attribute.name() == name;
		});

		if (it == std::end(attributes_))
			attributes_.push_back(attribute{name, ""});

		return attributes_.back().value();
	}

	inline bool tag::has_attribute(const std::string& name) const
	{
		return boost::find_if(attributes_, [&](const attribute& attribute)
		{
			return attribute.name() == name;
		}) != std::end(attributes_);
	}

	inline std::vector<boost::smatch> get_all_captures(const std::string& text, const boost::regex& pattern)
	{
		std::vector<boost::smatch> matches;

		auto it = boost::sregex_iterator{text.begin(), text.end(), pattern};
		const auto end = boost::sregex_iterator{};

		for (; it != end; ++it)
			if (it->size() > 1)
				matches.push_back(*it);

		return matches;
	}

	inline tag to_tag(std::string tag_name, const boost::smatch& match)
	{
		std::vector<attribute> attributes;
		std::string attributes_string = match[1];

		const auto captured_attributes = get_all_captures(attributes_string, patterns::tag_attribute());

		for (const boost::smatch& capture : captured_attributes)
			attributes.emplace_back(std::string{capture[1]}, std::string{capture[2]});

		return tag{std::move(tag_name), std::move(attributes)};
	}
}