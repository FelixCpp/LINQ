#pragma once

#include <algorithm>

#include "../concepts.hpp"
#include "../exceptions.hpp"

namespace linq
{
	template <typename Combinator>
	struct minmax_builder
	{
		Combinator combinator;

		constexpr explicit minmax_builder(Combinator combinator):
			combinator(std::move(combinator))
		{}

		template <concepts::range Range> requires requires (typename Range::reference lhs, typename Range::reference rhs)
		{
			lhs < rhs;
			std::invocable<Combinator, typename Range::value_type, typename Range::value_type>;
		}
		constexpr auto build(Range range) const -> std::invoke_result_t<Combinator, typename Range::value_type, typename Range::value_type>
		{
			if (not range.move_next())
			{
				throw empty_sequence_exception{};
			}

			auto min = range.get_value();
			auto max = min;

			while (range.move_next())
			{
				const auto value = range.get_value();
				min = std::min(min, value);
				max = std::max(max, value);
			}

			return combinator(min, max);
		}
	};

	template <typename Combinator>
	constexpr auto minmax(Combinator combinator)
	{
		return minmax_builder{ std::move(combinator) };
	}

	constexpr auto minmax()
	{
		return minmax([](const auto min, const auto max) { return std::make_pair(min, max); });
	}
}
