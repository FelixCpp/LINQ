#pragma once

#include "../concepts.hpp"

namespace linq
{
	template <typename Action>
	struct for_each_builder
	{
		Action action;

		constexpr explicit for_each_builder(Action action) :
			action(action)
		{}

		constexpr auto build(concepts::range auto range) const requires concepts::action<Action, typename decltype(range)::value_type>
		{
			while (range.move_next())
			{
				action(range.get_value());
			}
		}
	};

	constexpr auto for_each(auto predicate)
	{
		return for_each_builder{ std::move(predicate) };
	}
}