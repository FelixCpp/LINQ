#pragma once

#include "../concepts.hpp"
#include "../exceptions.hpp"

namespace linq
{
	struct no_element_found_exception final : std::exception
	{
		explicit no_element_found_exception(const char* msg) :
			exception(msg)
		{}
	};

	template <typename Predicate>
	struct first_builder
	{
		Predicate predicate;

		constexpr explicit first_builder(Predicate predicate) :
			predicate(std::move(predicate))
		{}

		constexpr auto build(concepts::range auto range) const -> decltype(range.get_value()) requires concepts::predicate<Predicate, typename decltype(range)::value_type>
		{
			if (not range.move_next())
			{
				throw empty_sequence_exception();
			}

			do
			{
				auto value = range.get_value();
				if (predicate(value))
				{
					return value;
				}
			} while (range.move_next());

			throw no_element_found_exception("No element satisfied the predicate.");
		}
	};

	constexpr auto first(auto predicate)
	{
		return first_builder{ std::move(predicate) };
	}

	constexpr auto first()
	{
		return first([](const auto _) { return true; });
	}
}