#pragma once

#include <string>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include "../../realms.hpp"
#include "../services.hpp"

namespace warmane::armory::api
{
	class target
	{
	public:
		target(
			const std::string& name,
			const armory::service service = armory::services::character,
			const warmane::realm realm = warmane::realms::icecrown
		);

		const std::string& name() const;
		armory::service service() const;
		warmane::realm realm() const;

		std::string path() const;

	private:
		std::string name_;
		armory::service service_;
		warmane::realm realm_;
	};

	inline target::target(const std::string& name, const armory::service service, const warmane::realm realm)
		: name_{name}
		, service_{service}
		, realm_{realm}
	{}

	inline const std::string& target::name() const
	{
		return name_;
	}

	inline armory::service target::service() const
	{
		return service_;
	}

	inline warmane::realm target::realm() const
	{
		return realm_;
	}

	inline std::string target::path() const
	{
		return fmt::format("/api/{}/{}/{}/summary", service_.name(), name_, realm_.name());
	}

	inline std::string encode_url(const std::string& url)
	{
		std::string encoded;

		for (const auto& c : url)
		{
			if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
			{
				encoded += c;
				continue;
			}

			encoded += fmt::format("%{:x}", std::toupper(c));
		}

		return encoded;
	}
}

