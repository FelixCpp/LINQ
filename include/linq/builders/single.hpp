#pragma once

#include "../concepts.hpp"
#include "../exceptions.hpp"

#include <optional>

namespace linq
{
	struct single_exception final : std::exception
	{
		single_exception() :
			exception("More than one elements inside sequence")
		{}
	};

	struct single_builder
	{
		constexpr auto build(concepts::range auto range) -> decltype(range.get_value())
		{
			if (not range.move_next())
			{
				throw empty_sequence_exception();
			}

			typename decltype(range)::reference result = range.get_value();

			if (range.move_next())
			{
				throw single_exception();
			}

			return result;
		}
	};

	constexpr auto single()
	{
		return single_builder{};
	}
}