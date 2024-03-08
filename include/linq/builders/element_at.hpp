#pragma once

#include <stdexcept>

#include "../concepts.hpp"

namespace linq
{
	struct element_at_builder
	{
		std::size_t index;

		constexpr explicit element_at_builder(const std::size_t index) :
			index(index)
		{}

		constexpr auto build(concepts::range auto range) -> decltype(range.get_value())
		{
			for (std::size_t i = 0; i <= index; ++i)
			{
				if (not range.move_next())
				{
					throw std::out_of_range("Index too large.");
				}
			}

			return range.get_value();
		}
	};

	constexpr auto element_at(const std::size_t index)
	{
		return element_at_builder{ index };
	}
}