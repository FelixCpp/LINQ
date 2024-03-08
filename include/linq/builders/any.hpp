#pragma once

#include "../concepts.hpp"

namespace linq
{
	template <typename Predicate>
	struct any_predicate_builder
	{
		Predicate predicate;

		constexpr explicit any_predicate_builder(Predicate predicate) :
			predicate(predicate)
		{}

		constexpr auto build(concepts::range auto range) requires concepts::predicate<Predicate, typename decltype(range)::value_type>
		{
			while (range.move_next())
			{
				if (predicate(range.get_value()))
				{
					return true;
				}
			}

			return false;
		}
	};

	constexpr auto any(auto predicate)
	{
		return any_predicate_builder{ std::move(predicate) };
	}

	constexpr auto any()
	{
		return any([](const auto _) { return true; });
	}
}