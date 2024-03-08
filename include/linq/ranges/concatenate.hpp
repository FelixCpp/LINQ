#pragma once

#include <assert.h>

#include "../concepts.hpp"

namespace linq
{
	template <concepts::range LhsRange, concepts::range RhsRange>
		requires std::same_as<typename LhsRange::value_type, typename RhsRange::value_type>
	struct concatenate_range
	{
		LhsRange lhs_range;
		RhsRange rhs_range;

		using value_type = typename LhsRange::value_type;
		using reference = typename LhsRange::reference;

		enum iteration_state_enum
		{
			initial,
			lhs,
			rhs,
			done
		} iteration_state;

		constexpr explicit concatenate_range(LhsRange lhs_range, RhsRange rhs_range):
			lhs_range(lhs_range),
			rhs_range(rhs_range),
			iteration_state(initial)
		{}

		reference get_value()
		{
			assert(iteration_state != initial && iteration_state != done);

			switch (iteration_state)
			{
				case lhs: return lhs_range.get_value();
				case rhs: return rhs_range.get_value();
			}
		}

		bool move_next()
		{
			switch (iteration_state)
			{
				case initial:
				{
					iteration_state = lhs;
					return move_next();
				}

				case lhs:
				{
					if (not lhs_range.move_next())
					{
						iteration_state = rhs;
						return move_next();
					}

					return true;
				}

				case rhs:
				{
					if (not rhs_range.move_next())
					{
						iteration_state = done;
						return false;
					}

					return true;
				}

				case done:
				default:
					return false;
			}
		}

		constexpr auto operator >> (auto builder) const -> decltype(builder.build(*this))
		{
			return builder.build(*this);
		}
	};

	template <concepts::range OuterRange>
	struct concatenate_builder
	{
		OuterRange outer_range;

		constexpr explicit concatenate_builder(OuterRange outer_range):
			outer_range(outer_range)
		{}

		template <concepts::range Range>
		constexpr auto build(Range range) const -> decltype(concatenate_range{ std::move(range), outer_range }) 
		{
			return concatenate_range{ std::move(range), outer_range };
		}
	};

	constexpr auto concatenate(concepts::range auto range)
	{
		return concatenate_builder{ std::move(range) };
	}
}
