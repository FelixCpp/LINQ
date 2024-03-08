#pragma once

#include <stdexcept>

namespace linq
{
	template <typename T>
	struct empty_range
	{
		using value_type = std::decay_t<T>;
		using reference = value_type&;

		reference get_value()
		{
			throw std::runtime_error("Cannot receive value from empty sequence.");
		}

		bool move_next()
		{
			return false;
		}

		constexpr auto operator >> (auto builder) const -> decltype(builder.build(*this))
		{
			return builder.build(*this);
		}
	};

	template <typename T>
	constexpr auto empty()
	{
		return empty_range<T>{};
	}
}