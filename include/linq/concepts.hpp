#pragma once

#include <ranges>

namespace linq::concepts
{
	template <typename Range>
	concept range = requires(Range range) {
		typename Range::value_type;

		{ range.move_next() } -> std::same_as<bool>;
		{ range.get_value() } -> std::same_as<typename Range::reference>;
	};

	template <typename Predicate, typename ... TArgs>
	concept predicate = requires(Predicate predicate, TArgs... args)
	{
		{ predicate(args...) } -> std::same_as<bool>;
	};
}