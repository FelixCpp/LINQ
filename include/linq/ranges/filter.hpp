#pragma once

#include "../concepts.hpp"

#include <type_traits>

namespace linq
{
	template <typename Range, typename Predicate>
		requires
			concepts::range<Range> and
			concepts::predicate<Predicate, typename Range::value_type>
	struct filter_range
	{
		using value_type = typename Range::value_type;
		using reference = typename Range::reference;

		Range range;
		Predicate predicate;

		constexpr explicit filter_range(Range range, Predicate predicate) :
			range(std::move(range)),
			predicate(std::move(predicate))
		{}

		constexpr reference get_value()
		{
			return range.get_value();
		}

		constexpr bool move_next()
		{
			while (range.move_next())
			{
				if (const auto value = range.get_value(); predicate(value))
				{
					return true;
				}
			}

			return false;
		}

		constexpr auto operator >> (auto builder) const -> decltype(builder.build(*this))
		{
			return builder.build(*this);
		}
	};

	template <typename Predicate>
	struct filter_builder
	{
		Predicate predicate;

		constexpr explicit filter_builder(Predicate predicate):
			predicate(std::move(predicate))
		{}

		constexpr auto build(concepts::range auto range) const -> decltype(filter_range{ std::move(range), predicate })
		{
			return filter_range{ std::move(range), predicate };
		}
	};

	constexpr auto filter(auto predicate)
	{
		return filter_builder{ std::move(predicate) };
	}

	constexpr auto filter_not(auto predicate)
	{
		return filter([predicate = std::move(predicate)](const auto value) { return !predicate(value); });
	}
}