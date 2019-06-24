#include <iostream>

#include "../include/warmane/api.hpp"

int main()
{
    std::cout << "Hello World!\n";

	auto api = warmane::api::connect();
	const auto results = api.get({"Act", warmane::services::character});
	for (const auto& result : results)
		std::cout << result.value() << ' ';
}
