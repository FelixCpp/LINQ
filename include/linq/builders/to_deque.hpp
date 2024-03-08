#pragma once

#include <deque>

#include "../concepts.hpp"

namespace linq
{
	struct to_deque_builder
	{
		constexpr auto build(concepts::range auto range)
		{
			using value_type = typename decltype(range)::value_type;

			std::deque<value_type> result;
			
			while (range.move_next())
			{
				result.push_back(range.get_value());
			}

			return result;
		}
	};

	constexpr auto to_deque()
	{
		return to_deque_builder{};
	}
}
