#ifndef _TAG_H_
#define _TAG_H_
#pragma once
#include <stdint.h>
#include "Destination.h"

#define CreateTag(destination, tag) ( (uint64_t(destination) << 32) | uint64_t(tag) )

namespace MPE
{
	namespace Tag
	{
		//! The basic tags used during message passing.
		enum : uint64_t
		{
			Any = CreateTag(Destination::ThreadMessageController, 0),
			Shutdown = CreateTag(Destination::ThreadMessageController, 1),
			Start = CreateTag(Destination::ThreadMessageController, 2),
			DeleteEntity = CreateTag(Destination::ThreadMessageController, 3)
		};	
	}
}
#endif