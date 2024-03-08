#pragma once

#include "../concepts.hpp"

#include <optional>

namespace linq
{
	template <typename Predicate>
	struct first_or_null_builder
	{
		Predicate predicate;

		constexpr explicit first_or_null_builder(Predicate predicate) :
			predicate(std::move(predicate))
		{}

		template <concepts::range Range>
		constexpr auto build(Range range) const -> std::optional<typename Range::value_type> requires concepts::predicate<Predicate, typename Range::value_type>
		{
			if (not range.move_next())
			{
				return std::nullopt;
			}

			do
			{
				auto value = range.get_value();
				if (predicate(value))
				{
					return value;
				}
			} while (range.move_next());

			return std::nullopt;
		}
	};

	constexpr auto first_or_null(auto predicate)
	{
		return first_or_null_builder{ std::move(predicate) };
	}

	constexpr auto first_or_null()
	{
		return first_or_null([](const auto _) { return true; });
	}
}