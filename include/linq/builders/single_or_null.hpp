#pragma once

#include "../concepts.hpp"

#include <optional>

namespace linq
{
	struct single_or_null_builder
	{
		template <concepts::range Range>
		constexpr auto build(Range range) -> std::optional<typename Range::value_type>
		{
			if (not range.move_next())
			{
				return std::nullopt;
			}

			auto result = range.get_value();

			if (range.move_next())
			{
				return std::nullopt;
			}

			return result;
		}
	};

	constexpr auto single_or_null()
	{
		return single_or_null_builder{};
	}
}