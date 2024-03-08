#pragma once

#include <optional>

#include "../concepts.hpp"

namespace linq
{

	template <concepts::range Range, typename Transformer>
	struct map_range
	{
		using value_type = std::invoke_result_t<Transformer, typename Range::value_type>;
		using reference = value_type&;

		Range range;
		Transformer transformer;
		std::optional<value_type> cache;

		constexpr explicit map_range(Range range, Transformer transformer):
			range(range),
			transformer(transformer),
			cache(std::nullopt)
		{}

		[[nodiscard]] reference get_value()
		{
			assert(cache.has_value());
			return cache.value();
		}

		[[nodiscard]] bool move_next()
		{
			if (range.move_next())
			{
				cache = transformer(range.get_value());
			} else
			{
				cache.reset();
			}

			return cache.has_value();
		}

		constexpr auto operator >> (auto builder) const -> decltype(builder.build(*this))
		{
			return builder.build(*this);
		}
	};

	template <typename Transformer>
	struct map_builder
	{
		Transformer transformer;

		constexpr explicit map_builder(Transformer transformer):
			transformer(transformer)
		{}

		constexpr auto build(concepts::range auto range) -> decltype(map_range{ std::move(range), transformer })
		{
			return map_range{ std::move(range), transformer };
		}
	};

	constexpr auto map(auto transformer)
	{
		return map_builder{ transformer };
	}
	
}
