#pragma once

#include "../concepts.hpp"

namespace linq
{

	struct empty_builder
	{
		constexpr auto build(concepts::range auto range)
		{
			return not range.move_next();
		}
	};

	constexpr auto empty()
	{
		return empty_builder{};
	}

}