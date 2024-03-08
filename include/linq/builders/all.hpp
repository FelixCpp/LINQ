#pragma once

#include "../concepts.hpp"

namespace linq
{
	template <typename Predicate>
	struct all_predicate_builder
	{
		Predicate predicate;

		constexpr explicit all_predicate_builder(Predicate predicate) :
			predicate(predicate)
		{}

		constexpr auto build(concepts::range auto range) requires concepts::predicate<Predicate, typename decltype(range)::value_type>
		{
			while (range.move_next())
			{
				if (!predicate(range.get_value()))
				{
					return false;
				}
			}

			return true;
		}
	};

	constexpr auto all(auto predicate)
	{
		return all_predicate_builder{ std::move(predicate) };
	}

	constexpr auto none(auto predicate)
	{
		return all([predicate = std::move(predicate)](const auto value) { return !predicate(value); });
	}
}