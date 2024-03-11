#pragma once

#include <ranges>

namespace linq::concepts
{
	template <typename Range>
	concept range = requires(Range range) {
		typename Range::value_type;

		std::is_const_v<typename Range::reference>;
		{ range.move_next() } -> std::same_as<bool>;
		{ range.get_value() } -> std::same_as<typename Range::reference>;
	};

	template <typename Predicate, typename ... TArgs>
	concept predicate = requires(Predicate predicate, TArgs... args)
	{
		{ predicate(args...) } -> std::same_as<bool>;
	};

	template <typename Action, typename ... TArgs>
	concept action = requires(Action action, TArgs... args)
	{
		{ action(args...) } -> std::same_as<void>;
	};

	template <typename Transformer, typename ... TArgs>
	concept transformer = requires(Transformer transformer, TArgs... args)
	{
		not std::is_void_v<std::invoke_result_t<Transformer, TArgs...>>;
	};
}