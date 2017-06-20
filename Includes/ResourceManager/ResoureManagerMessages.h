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
			//! The tags used in the ResourceManager
			enum : uint64_t
			{
				LoadResource = CreateTag(Destination::ResourceManager, 0),
				LoadResourceAndForward = CreateTag(Destination::ResourceManager, 1),
				LoadResourceResponse = CreateTag(Destination::ResourceManager, 2),
				UnloadResource = CreateTag(Destination::ResourceManager, 3)
			};
			//! Struct used when requesting to unload a resource.
			struct UnloadResourceStruct
			{
				static UnloadResourceStruct* Create(const GUID&& guid)
				{
					auto r = CreateNew(UnloadResourceStruct);
					return r;
				}
				GUID guid;
			};

			//! Struct used when requesting a resource to be loaded.
			struct LoadResourceStruct
			{
				//! Create an instance of LoadResourceStruct
				/*!
				This is used since the data in a msg needs to be cleaned when the message has been read.
				\param guid The GUID of the resource to load.
				\param tag The message the resource manager should respond with.
				\param dest Specify who should recieve the data of the loaded resource, this option is only used when LoadResourceAndForward is used, otherwise it is ignored.
				\param priority The priority the response message should have.
				*/
				static LoadResourceStruct* Create(const GUID& guid, uint64_t tag, uint32_t dest = 0, uint8_t priority = 0)
				{
					auto r = CreateNew(LoadResourceStruct);
					r->guid = guid;
					r->tag = tag;
					r->dest = dest;
					r->prio = priority;
					return r;
				}
				//! Create an instance of LoadResourceStruct
				/*!
				This is used since the data in a msg needs to be cleaned when the message has been read.
				\param guid The GUID of the resource to load.
				\param tag The message the resource manager should respond with.
				\param dest Specify who should recieve the data of the loaded resource, this option is only used when LoadResourceAndForward is used, otherwise it is ignored.
				\param priority The priority the response message should have.
				*/
				static LoadResourceStruct* Create(const GUID&& guid, uint64_t tag, uint32_t dest = 0, uint8_t priority = 0)
				{
					auto r = CreateNew(LoadResourceStruct);
					r->guid = guid;
					r->tag = tag;
					r->dest = dest;
					r->prio = priority;
					return r;
				}
				GUID guid;
				uint64_t tag;
				uint32_t dest;
				uint8_t prio;
			private:
				LoadResourceStruct() = delete;
			};

			//! Struct that contains resource data. Used when sending the LoadResourceResponse message.
			struct ResouceData
			{
				//! Create an instance of ResouceData
				/*!
				This is used since the data in a msg needs to be cleaned when the message has been read.
				\param data A pointer to the resource data.
				\param size The size of the data.
				\param tag The message specified when requesting a resource.(The same as LoadResourceStruct::tag)
				*/
				static ResouceData* Create(const GUID& guid, void*data, size_t size, uint64_t tag)
				{
					auto r = CreateNew(ResouceData);
					r->guid = guid;
					r->data = data;
					r->size = size;
					r->tag = tag;
					return r;
				}
				//! Create an instance of ResouceData
				/*!
				This is used since the data in a msg needs to be cleaned when the message has been read.
				\param data A pointer to the resource data.
				\param size The size of the data.
				\param tag The message specified when requesting a resource.(The same as LoadResourceStruct::tag)
				*/
				static ResouceData* Create(const GUID&& guid, void*data, size_t size, uint64_t tag)
				{
					auto r = CreateNew(ResouceData);
					r->guid = guid;
					r->data = data;
					r->size = size;
					r->tag = tag;
					return r;
				}
				GUID guid;
				void* data;
				size_t size;				
				uint64_t tag;
			private:
				ResouceData() = delete;
			};
		};
		
		
	}


	
}
#endif