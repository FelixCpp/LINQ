#pragma once

#include "../concepts.hpp"

namespace linq
{
	template <typename Predicate>
	struct count_predicate_builder
	{
		Predicate predicate;

		constexpr explicit count_predicate_builder(Predicate predicate):
			predicate(predicate)
		{}

		constexpr auto build(concepts::range auto range) requires concepts::predicate<Predicate, typename decltype(range)::value_type>
		{
			std::size_t count = 0;
			while (range.move_next())
			{
				if (predicate(range.get_value()))
				{
					++count;
				}
			}
			return count;
		}
	};

	constexpr auto count(auto predicate)
	{
		return count_predicate_builder{ std::move(predicate) };
	}

	constexpr auto count()
	{
		return count_predicate_builder{ [](const auto _) { return true; } };
	}
}