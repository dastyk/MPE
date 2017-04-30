
#pragma once
#include "Entity.h"
#include <unordered_map>


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
	class Manager
	{
	protected:
		Manager();
		virtual ~Manager();


	};
}

