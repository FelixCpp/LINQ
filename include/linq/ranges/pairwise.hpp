#pragma once

#include <cassert>
#include <optional>

#include "../concepts.hpp"

namespace linq
{

	template <
		concepts::range Range,
		typename Combinator
	>
	struct pairwise_range
	{
		using value_type = std::invoke_result_t<Combinator, typename Range::value_type, typename Range::value_type>;
		using reference = value_type;

		Range range;
		Combinator combinator;
		bool initial;

		std::optional<typename Range::value_type> current;
		std::optional<typename Range::value_type> next;

		constexpr explicit pairwise_range(Range range, Combinator combinator):
			range(std::move(range)),
			combinator(std::move(combinator)),
			initial(true),
			current(std::nullopt),
			next(std::nullopt)
		{}

		constexpr reference get_value()
		{
			assert(current.has_value() and next.has_value());

			const auto lhs = current.value();
			const auto rhs = next.value();
			return combinator(lhs, rhs);
		}

		constexpr bool move_next()
		{
			if (const bool initialIteration = not current.has_value())
			{
				if (range.move_next())
				{
					current = range.get_value();
				} else
				{
					return false;
				}
			} else
			{
				current.swap(next);
			}

			if (range.move_next())
			{
				next = range.get_value();
			} else
			{
				next.reset();
			}

			return current.has_value() and next.has_value();
			
		}

		constexpr auto operator >> (auto builder) const -> decltype(builder.build(*this))
		{
			return builder.build(*this);
		}
	};

	template <typename Combinator>
	struct pairwise_builder
	{
		Combinator combinator;

		constexpr explicit pairwise_builder(Combinator combinator):
			combinator(std::move(combinator))
		{}

		constexpr auto build(concepts::range auto range) const
		{
			return pairwise_range{ std::move(range), combinator };
		}
	};

	template <typename Combinator>
	constexpr auto pairwise(Combinator combinator)
	{
		return pairwise_builder{ std::move(combinator) };
	}

	constexpr auto pairwise()
	{
		return pairwise_builder{ [](const auto lhs, const auto rhs) { return std::make_pair(lhs, rhs); } };
	}

}
