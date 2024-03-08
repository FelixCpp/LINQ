#pragma once

#include "../concepts.hpp"

#include <cassert>

namespace linq
{
	template <concepts::range Range>
	struct skip_range
	{
		using value_type = typename Range::value_type;
		using reference = typename Range::reference;

		Range range;
		std::size_t count;
		std::size_t skipped;

		constexpr explicit skip_range(Range range, const std::size_t count) :
			range(std::move(range)),
			count(count),
			skipped(0)
		{}

		reference get_value()
		{
			assert(skipped > count);
			return range.get_value();
		}

		bool move_next()
		{
			while (skipped++ < count)
			{
				if (!range.move_next())
				{
					return false;
				}
			}

			return range.move_next();
		}

		constexpr auto operator >> (auto builder) const -> decltype(builder.build(*this))
		{
			return builder.build(*this);
		}
	};

	struct skip_builder
	{
		std::size_t count;

		constexpr explicit skip_builder(const std::size_t count) :
			count(count)
		{}

		constexpr auto build(concepts::range auto range) -> decltype(skip_range{ std::move(range), count })
		{
			return skip_range{ std::move(range), count };
		}
	};

	constexpr auto skip(const std::size_t count)
	{
		return skip_builder{ count };
	}

}