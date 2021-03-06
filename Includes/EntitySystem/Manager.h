#include <ThreadMessageControl\Thread.h>

#pragma once
#include "Entity.h"
#include <unordered_map>

#ifdef _DEBUG
#pragma comment(lib, "ThreadMessageControlD.lib")
#else
#pragma comment(lib, "ThreadMessageControl.lib")
#endif

namespace MPE
{
	//! The memory where the data for each entity entry is held.
	/*!
	Each array has the same number of entires and are concatenated in the memory block.
	*/
	struct BaseManagerEntityEntryBlock
	{
		uint32_t used = 0; /*!< Currently used entires in the block */  
		uint32_t allocated = 0; /*!< Currently allocated entires in the block */  
		void *buffer = nullptr; /*!< Pointer to the memory block*/  

		Entity* entity;	/*!< Stores the entity the entry is assigned to */  
	};

	//! The manager base class
	/*!
	This is a virtual class and is intended to be inherited by classes that are to be used for managing entities
	*/
	class Manager : public Thread
	{
	protected:
		Manager(threadIdentifier identifier, uint8_t frameSyncTime = 16);
		virtual ~Manager();


	};
}

