#pragma once

#include "../concepts.hpp"
#include "../exceptions.hpp"

#include <algorithm>

namespace linq
{
	struct max_builder
	{
		template <concepts::range Range> requires requires (typename Range::reference lhs, typename Range::reference rhs)
		{
			lhs < rhs;
		}
		constexpr auto build(Range range) const -> typename Range::value_type
		{
			if (not range.move_next())
			{
				throw empty_sequence_exception{};
			}

			auto result = range.get_value();

			while (range.move_next())
			{
				result = std::max(result, range.get_value());
			}

			return result;
		}
	};

	constexpr auto max()
	{
		return max_builder{};
	}
}
