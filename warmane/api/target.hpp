#pragma once

#include <string>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include "../realms.hpp"
#include "../services.hpp"

namespace warmane::api
{
	class target
	{
	public:
		target(const std::string& name, const warmane::service service = warmane::services::character, const warmane::realm realm = warmane::realms::icecrown);

		const std::string& name() const;
		warmane::service service() const;
		warmane::realm realm() const;

		std::string encode_url() const;

	private:
		std::string name_;
		warmane::service service_;
		warmane::realm realm_;
	};

	inline target::target(const std::string& name, const warmane::service service, const warmane::realm realm)
		: name_{name}
		, service_{service}
		, realm_{realm}
	{}

	inline const std::string& target::name() const
	{
		return name_;
	}

	inline warmane::service target::service() const
	{
		return service_;
	}

	inline warmane::realm target::realm() const
	{
		return realm_;
	}

	inline std::string target::encode_url() const
	{
		//http://armory.warmane.com/api/guild/The+Sanctuary/Frostwolf/summary

		return fmt::format("{}/api/{}/{}/{}/summary", warmane::hostname(), service_.name(), name_, realm_);
	}
}

