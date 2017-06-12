
#pragma once
#include "Entity.h"
#include <unordered_map>
#include <selene.h>

#ifdef _DEBUG
#pragma comment(lib, "LuaWrapperD.lib")
#else
#pragma comment(lib, "LuaWrapper.lib")
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
	class Manager
	{
	protected:
		Manager();
		virtual ~Manager();

	public:
		//! Registers all the lua functions, etc. for the manager.
		virtual const void RegisterScriptStuff(sel::State& _state) = 0;
	};
}

