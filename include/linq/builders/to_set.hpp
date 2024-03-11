#pragma once

#include <set>
#include <unordered_set>

#include "../concepts.hpp"

namespace linq
{
	template <template <typename> typename Set>
	struct to_set_builder
	{
		template <concepts::range Range>
		constexpr auto build(Range range) const
		{
			using value_type = typename Range::value_type;
			Set<value_type> result;
			
			while (range.move_next())
			{
				const auto value = range.get_value();
				result.insert(result.end(), value);
			}

			return result;
		}
	};

	constexpr auto to_set()
	{
		return to_set_builder<std::set>{};
	}

	constexpr auto to_multiset()
	{
		return to_set_builder<std::multiset>{};
	}

	constexpr auto to_unordered_set()
	{
		return to_set_builder<std::unordered_set>{};
	}

	constexpr auto to_unordered_multiset()
	{
		return to_set_builder<std::unordered_multiset>{};
	}
}