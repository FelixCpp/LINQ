#pragma once

#include <unordered_set>

#include "../concepts.hpp"

namespace linq
{
	struct to_unordered_set_builder
	{
		std::size_t capacity;

		constexpr explicit to_unordered_set_builder(const std::size_t capacity):
			capacity(capacity)
		{}

		constexpr auto build(concepts::range auto range)
		{
			using value_type = typename decltype(range)::value_type;

			std::unordered_set<value_type> result;
			result.reserve(capacity);

			while (range.move_next())
			{
				result.insert(result.end(), range.get_value());
			}

			return result;
		}
	};

	constexpr auto to_unordered_set(const std::size_t capacity = 16)
	{
		return to_unordered_set_builder{ capacity };
	}
}
