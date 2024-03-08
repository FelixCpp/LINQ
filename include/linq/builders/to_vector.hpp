#pragma once

#include <vector>

#include "../concepts.hpp"

namespace linq
{
	struct to_vector_builder
	{
		std::size_t capacity;

		constexpr explicit to_vector_builder(const std::size_t capacity):
			capacity(capacity)
		{}

		constexpr auto build(concepts::range auto range)
		{
			using value_type = typename decltype(range)::value_type;

			std::vector<value_type> result;
			result.reserve(capacity);

			while (range.move_next())
			{
				result.push_back(range.get_value());
			}

			return result;
		}
	};

	constexpr auto to_vector(const std::size_t capacity = 16)
	{
		return to_vector_builder{ capacity };
	}
}
