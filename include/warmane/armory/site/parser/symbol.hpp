#pragma once

#include <string>
#include <ostream>

#include "error.hpp"

namespace warmane::armory::site::parser
{
	enum class symbol
	{
		div, h3, script, class_, span, id, content, eof
	};

	symbol to_symbol(const std::string& text)
	{
		if (text == "div")
			return symbol::div;

		else if (text == "h3")
			return symbol::h3;

		else if (text == "script")
			return symbol::script;

		else if (text == "class")
			return symbol::class_;

		else if (text == "span")
			return symbol::span;

		else if (text == "id")
			return symbol::id;

		else if (text == "content")
			return symbol::content;

		else if (text == "$")
			return symbol::eof;

		throw unexpected_token{"[parser::to_symbol] Invalid symbol string"};
	}

	template <class String>
	String to_string(const symbol s)
	{
		switch (s)
		{
		case symbol::div: return String{"div"};
		case symbol::h3: return String{"h3"};
		case symbol::script: return String{"script"};
		case symbol::class_: return String{"class"};
		case symbol::span: return String{"span"};
		case symbol::id: return String{"id"};
		case symbol::content: return String{"content"};
		case symbol::eof: return String{"$"};
		}

		return String{"<invalid symbol>"};
	}

	const char* to_string(const symbol s)
	{
		return to_string<const char*>(s);
	}

	inline std::ostream& operator<<(std::ostream& stream, const symbol s)
	{
		stream << to_string(s);
		return stream;
	}

}