#ifndef _RESOURCE_MANAGER_MESSAGES_H_
#define _RESOURCE_MANAGER_MESSAGES_H_
#pragma once
#include <stdint.h>
#include <ThreadMessageControl\Tag.h>
#include "GUID.h"

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

			struct LoadResourceStruct
			{
				static LoadResourceStruct* Create(GUID guid, uint8_t priority = 0)
				{
					auto r = (LoadResourceStruct*)operator new(sizeof(LoadResourceStruct));
					r->guid = guid;
					r->priority = priority;

					return r;
				}
				GUID guid;
				uint8_t priority;
			private:
				LoadResourceStruct() = delete;
			};
		};
		
		
	}


	
}
#endif