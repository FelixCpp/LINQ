#pragma once

#include "../concepts.hpp"

namespace linq
{

	struct is_empty_builder
	{
		constexpr auto build(concepts::range auto range)
		{
			return not range.move_next();
		}
	};

	constexpr auto is_empty()
	{
		return is_empty_builder{};
	}

}