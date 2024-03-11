#pragma once

#include <cassert>

namespace linq
{
	template <typename T>
	struct repeat_range
	{
		using value_type = std::decay_t<T>;
		using reference = const value_type&;

		value_type value;
		std::size_t count;
		std::size_t repetitions;

		constexpr explicit repeat_range(value_type value, const std::size_t count):
			value(value),
			count(count),
			repetitions(0)
		{}

		constexpr reference get_value()
		{
			assert(repetitions <= count);
			return value;
		}

		constexpr bool move_next()
		{
			return repetitions++ < count;
		}

		constexpr auto operator >> (auto builder) const -> decltype(builder.build(*this))
		{
			return builder.build(*this);
		}
	};

	template <typename T>
	constexpr auto repeat(T value, const std::size_t repetitions) -> decltype(repeat_range<T>{ value, repetitions })
	{
		return repeat_range<T>{ value, repetitions };
	}
}