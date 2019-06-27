#pragma once

#include <array>

namespace warmane::utlity
{
	template <class... Ts>
	constexpr auto make_array(Ts&& ... ts)
	{
		return std::array<std::common_type_t<Ts...>, sizeof...(Ts)>{
			std::forward<Ts>(ts)...
		};
	}
}