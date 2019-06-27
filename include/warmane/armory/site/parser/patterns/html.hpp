#pragma once

#include <boost/regex.hpp>

namespace warmane::armory::site::parser::patterns
{
	const boost::regex& tag_div()
	{
		thread_local const auto pattern = boost::regex{
			R"(<div ((?:[a-z]+="[A-Za-z -]+"[ ]*)+)>)",
			boost::regex_constants::optimize
		};

		return pattern;
	}

	const boost::regex& tag_span()
	{
		thread_local const auto pattern = boost::regex{
			R"(<span ((?:[a-z]+="[A-Za-z -]+"[ ]*)+)>)",
			boost::regex_constants::optimize
		};

		return pattern;
	}

	const boost::regex& tag_content()
	{
		thread_local const auto pattern = boost::regex{
			R"(>([^<>]+)<)",
			boost::regex_constants::optimize
		};

		return pattern;
	}

	const boost::regex& tag_attribute()
	{
		thread_local const auto pattern = boost::regex{
			R"(([-a-zA-Z]+)="([a-zA-Z -]*)\")",
			boost::regex_constants::optimize
		};

		return pattern;
	}
}