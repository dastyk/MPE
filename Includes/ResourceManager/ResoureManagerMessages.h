#ifndef _RESOURCE_MANAGER_MESSAGES_H_
#define _RESOURCE_MANAGER_MESSAGES_H_
#pragma once
#include <stdint.h>
#include <ThreadMessageControl\Tag.h>
namespace MPE
{
	namespace Tag
	{
		namespace ResourceManager
		{
			enum : uint64_t
			{
				LoadResource = CreateTag(Destination::ResourceManager, 0),
				LoadResourceAndForward = CreateTag(Destination::ResourceManager, 1),
			};
		};	
	}
	struct LoadResourceStruct
	{
		uint8_t priority;
	};
}
#endif