#pragma once

#include <list>

#include "../concepts.hpp"

namespace linq
{
	struct to_list_builder
	{
		constexpr auto build(concepts::range auto range)
		{
			using value_type = typename decltype(range)::value_type;

			std::list<value_type> result;
			
			while (range.move_next())
			{
				result.push_back(range.get_value());
			}

			return result;
		}
	};

	constexpr auto to_list()
	{
		return to_list_builder{};
	}
}
