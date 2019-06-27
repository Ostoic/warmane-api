#pragma once

#include <string>

namespace warmane::armory::site::parser::html
{
//interface:
	class attribute
	{
	public:
		explicit attribute(const std::string& name, const std::string& value);

		const std::string& name() const noexcept;
		const std::string& value() const noexcept;

	private:
		std::string name_;
		std::string value_;
	};


//impl:
	attribute::attribute(const std::string& name, const std::string& value)
		: name_{name}, value_{value}
	{}

	const std::string& attribute::name() const noexcept
	{
		return name_;
	}

	const std::string& attribute::value() const noexcept
	{
		return value_;
	}
}