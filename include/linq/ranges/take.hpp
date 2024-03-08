#pragma once

#include "../concepts.hpp"

#include <cassert>

namespace linq
{
	template <concepts::range Range>
	struct take_range
	{
		using value_type = typename Range::value_type;
		using reference = typename Range::reference;

		Range range;
		std::size_t count;
		std::size_t taken;

		constexpr explicit take_range(Range range, std::size_t count) :
			range(std::move(range)),
			count(count),
			taken(0)
		{}

		reference get_value()
		{
			//assert(taken < count);
			return range.get_value();
		}

		bool move_next()
		{
			if (taken >= count)
			{
				return false;
			}

			++taken;
			return range.move_next();
		}

		constexpr auto operator >> (auto builder) -> decltype(builder.build(*this))
		{
			return builder.build(*this);
		}
	};

	struct take_builder
	{
		std::size_t count;

		constexpr explicit take_builder(const std::size_t count):
			count(count)
		{}

		constexpr auto build(concepts::range auto range) -> decltype(take_range{ std::move(range), count })
		{
			return take_range{ std::move(range), count };
		}
	};

	constexpr auto take(const std::size_t count)
	{
		return take_builder{ count };
	}

}