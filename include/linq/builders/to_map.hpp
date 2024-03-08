#pragma once

#include <map>
#include <unordered_map>

#include "../concepts.hpp"

namespace linq
{
	template <typename KeySelector, typename ValueTransformer, template <typename, typename> typename Map>
	struct to_map_builder
	{
		KeySelector key_selector;
		ValueTransformer value_transformer;

		constexpr explicit to_map_builder(KeySelector key_selector, ValueTransformer value_transformer):
			key_selector(std::move(key_selector)),
			value_transformer(std::move(value_transformer))
		{}

		template <concepts::range Range> requires
			not std::is_same_v<
				std::invoke_result_t<
					KeySelector,
					std::invoke_result_t<ValueTransformer, typename Range::value_type>
				>, void
			>
		constexpr auto build(Range range)
		{
			using value_type = typename Range::value_type;
			using key_type = std::invoke_result_t<KeySelector, value_type>;

			Map<key_type, value_type> result;

			while (range.move_next())
			{
				const auto value = value_transformer(range.get_value());
				const auto key = key_selector(value);
				const auto entry = std::make_pair(key, value);

				result.insert(entry);
			}

			return result;
		}
	};

	template <typename KeySelector, typename ValueTransformer>
	constexpr auto to_map(KeySelector key_selector, ValueTransformer value_transformer)
	{
		return to_map_builder<KeySelector, ValueTransformer, std::map>{ std::move(key_selector), std::move(value_transformer) };
	}

	constexpr auto to_map(auto key_selector)
	{
		return to_map(std::move(key_selector), [](const auto input) { return input; });
	}

	template <typename KeySelector, typename ValueTransformer>
	constexpr auto to_unordered_map(KeySelector key_selector, ValueTransformer value_transformer)
	{
		return to_map_builder<KeySelector, ValueTransformer, std::unordered_map>{ std::move(key_selector), std::move(value_transformer) };
	}

	constexpr auto to_unordered_map(auto key_selector)
	{
		return to_unordered_map(std::move(key_selector), [](const auto input) { return input; });
	}

	template <typename KeySelector, typename ValueTransformer>
	constexpr auto to_multimap(KeySelector key_selector, ValueTransformer value_transformer)
	{
		return to_map_builder<KeySelector, ValueTransformer, std::multimap>{ std::move(key_selector), std::move(value_transformer) };
	}

	constexpr auto to_multimap(auto key_selector)
	{
		return to_multimap(std::move(key_selector), [](const auto input) { return input; });
	}

	template <typename KeySelector, typename ValueTransformer>
	constexpr auto to_unordered_multimap(KeySelector key_selector, ValueTransformer value_transformer)
	{
		return to_map_builder<KeySelector, ValueTransformer, std::unordered_multimap>{ std::move(key_selector), std::move(value_transformer) };
	}

	constexpr auto to_unordered_multimap(auto key_selector)
	{
		return to_unordered_multimap(std::move(key_selector), [](const auto input) { return input; });
	}
}
