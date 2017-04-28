#ifndef _DESTINATION_H_
#define _DESTINATION_H_

#pragma once
#include <stdint.h>
namespace MPE
{
	namespace Destination
	{
		enum : uint32_t
		{
			ThreadMessageController = 0, /**< 0 is reserved for ThreadMessageController. */
			Any = UINT32_MAX,/**< Specify to allow messages from any source. */
			DataManager = 1 << 0,
			ScriptManager = 1 << 1,
			Renderer = 1 << 2,
			ResourceManager = 1 << 3
		};

	}
}
#endif