#pragma once

#include "../http/target.hpp"

namespace warmane::armory::api
{
	class target : public http::target
	{
	public:
		target(
			const char* name,
			const warmane::realm realm = realms::icecrown,
			const armory::service service = services::character
		)
			: http::target{name, "/api", realm, service}
		{}
	};
}
