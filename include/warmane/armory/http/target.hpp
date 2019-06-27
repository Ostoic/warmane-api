#pragma once

#include "../../config.hpp"

#include <string>
#include <fmt/format.h>

#include "../../realms.hpp"
#include "../services.hpp"

#include <memory>

namespace warmane::armory::http
{
	class target
	{
	public:
		const std::string& name() const;
		std::string path() const;
		warmane::realm realm() const;
		armory::service service() const;

	protected:
		target(
			const std::string& name,
			const std::string& path = "/api",
			const warmane::realm realm = warmane::realms::icecrown,
			const armory::service service = armory::services::character
		);

	private:
		std::string name_;
		std::string path_;
		warmane::realm realm_;
		armory::service service_;
	};

	inline target::target(
		const std::string& name,
		const std::string& path,
		const warmane::realm realm,
		const armory::service service
	)
		: name_{name}
		, path_{path}
		, realm_{realm}
		, service_{service}
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
		return fmt::format("{}/{}/{}/{}/summary", path_, service_.name(), name_, realm_.name());
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

