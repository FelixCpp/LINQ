#pragma once

#include <string>
#include <vector>

#include "../concepts.hpp"

namespace linq
{
	template <
		typename Char,
		typename ValueTransformer
	>
	struct join_to_string_builder
	{
		using string = std::basic_string<Char>;

		string separator;
		ValueTransformer value_transformer;

		constexpr explicit join_to_string_builder(string separator, ValueTransformer value_transformer):
			separator(std::move(separator)),
			value_transformer(std::move(value_transformer))
		{}

		constexpr auto build(concepts::range auto range) const
		{
			std::vector<Char> buffer;
			buffer.reserve(16);

			for (std::size_t i = 0; range.move_next(); ++i)
			{
				if (i > 0)
				{
					buffer.append_range(separator);
				}

				const auto value = value_transformer(range.get_value());
				buffer.append_range(value);
			}

			return string(buffer.cbegin(), buffer.cend());
		}
	};

	template <typename ValueTransformer>
	constexpr auto join_to_string(ValueTransformer value_transformer, std::string separator)
	{
		return join_to_string_builder{ std::move(separator), std::move(value_transformer) };
	}

	constexpr auto join_to_string(std::string separator)
	{
		return join_to_string_builder{ std::move(separator), [](const auto input) { return input; } };
	}

	template <typename ValueTransformer>
	constexpr auto join_to_string(ValueTransformer value_transformer, std::wstring separator)
	{
		return join_to_string_builder{ std::move(separator), std::move(value_transformer) };
	}

	constexpr auto join_to_string(std::wstring separator)
	{
		return join_to_string_builder{ std::move(separator), [](const auto input) { return input; } };
	}
}
