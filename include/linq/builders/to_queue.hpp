#pragma once

#include <queue>

#include "../concepts.hpp"

namespace linq
{
	struct to_queue_builder
	{
		constexpr auto build(concepts::range auto range)
		{
			using value_type = typename decltype(range)::value_type;

			std::queue<value_type> result;

			while (range.move_next())
			{
				result.push(range.get_value());
			}

			return result;
		}
	};

	constexpr auto to_queue()
	{
		return to_queue_builder{};
	}
}
