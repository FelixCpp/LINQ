#pragma once

#include <set>

#include "../concepts.hpp"

namespace linq
{
	struct to_set_builder
	{
		constexpr auto build(concepts::range auto range)
		{
			using value_type = typename decltype(range)::value_type;

			std::set<value_type> result;

			while (range.move_next())
			{
				result.insert(result.end(), range.get_value());
			}

			return result;
		}
	};

	constexpr auto to_set()
	{
		return to_set_builder{};
	}
}
