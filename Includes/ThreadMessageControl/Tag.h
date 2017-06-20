#ifndef _TAG_H_
#define _TAG_H_
#pragma once
#include <stdint.h>
#include "Destination.h"

#define CreateTag(destination, tag) ( (uint64_t(destination) << 32) | uint64_t(tag) )
#define GetDestination(tag) (uint32_t(uint64_t(tag) >> 32))
#define CreateNew(type) (type*)operator new(sizeof(type));
namespace MPE
{
	namespace Tag
	{
		//! The basic tags used during message passing.
		/*!
		The first 32 bits is used for the destination, the next 32 is the message.
		*/
		enum : uint64_t
		{
			Any = CreateTag(Destination::ThreadMessageController, 0),
			Shutdown = CreateTag(Destination::ThreadMessageController, 1),
			Start = CreateTag(Destination::ThreadMessageController, 2),
		};	
	}
}
#endif