#pragma once

#include <stdint.h>
namespace MPE
{
	namespace Destination
	{
		static const uint32_t ThreadMessageController = 0; /**< Soruce 0 is reserved for ThreadMessageController. */
		static const uint32_t Any = UINT32_MAX;/**< Specify to allow messages from any source. */
		static const uint32_t DataManager = 1 << 0;
		static const uint32_t ScriptManager = 1 << 1;
		static const uint32_t Renderer = 1 << 2;
	}
}