#pragma once

#include <forward_list>

#include "../concepts.hpp"

namespace linq
{
	struct to_forward_list_builder
	{
		constexpr auto build(concepts::range auto range)
		{
			using value_type = typename decltype(range)::value_type;

			std::forward_list<value_type> result;
			
			while (range.move_next())
			{
				result.push_front(range.get_value());
			}

			return result;
		}
	};

	constexpr auto to_forward_list()
	{
		return to_forward_list_builder{};
	}
}
