#pragma once

#include <cassert>
#include <cstdint>
#include <xutility>

namespace linq
{
	template <typename Iterator>
	struct from_range
	{
		using value_type = typename std::iterator_traits<Iterator>::value_type;
		using reference = typename std::iterator_traits<Iterator>::reference;

		Iterator current;
		Iterator next;
		Iterator end;

		constexpr explicit from_range(Iterator begin, Iterator end):
			current(begin), next(begin), end(end)
		{}

		reference get_value() const
		{
			assert(current != end);
			return *current;
		}

		bool move_next()
		{
			if (next == end)
			{
				return false;
			}

			current = next;
			++next;
			return true;
		}
	};

	template <typename T, size_t Size>
	constexpr auto from(T(&array)[Size])
	{
		const auto begin = std::begin(array);
		const auto end = std::end(array);
		return from_range(begin, end);
	}

	template <typename Container>
	constexpr auto from(Container& container)
	{
		const auto begin = container.begin();
		const auto end = container.end();
		return from_range(begin, end);
	}

	template <typename Container>
	constexpr auto from(const Container& container)
	{
		const auto begin = container.cbegin();
		const auto end = container.cend();
		return from_range(begin, end);
	}

	template <typename Iterator>
	constexpr auto from(Iterator begin, Iterator end)
	{
		return from_range(begin, end);
	}
}