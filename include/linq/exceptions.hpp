#pragma once

#include <stdexcept>

namespace linq
{

	struct empty_sequence_exception final : std::exception
	{
		empty_sequence_exception():
			exception("Method was called on empty sequence")
		{}
	};
	
}