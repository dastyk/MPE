#ifndef _DATA_MANAGER_H_
#define _DATA_MANAGER_H_
#pragma once
#include "Manager.h"

namespace MPE
{

	class DataManager : public Manager
	{
	private:
		//! For the kinds of data that can be stored as an entry.
		enum class DataType : uint8_t
		{
			BOOL, FLOAT, STRING
		};

		//! Used for indexing the strings and other growing datatypes in the value_buffer.
		struct Data
		{
			uint16_t offset;
			uint16_t size;
		};

		//! The value struct, this is where the data is stored.
		/*!
		 The union clumps the memorylocation of all the members to the same position.
		 They share the same spot.
		*/
		struct Value
		{
			union
			{
				bool b;
				float f;
				Data data; // str
			};
		};

		//! The header struct, used for keeping track of the data entries an entity has.
		struct EntryHeader
		{
			uint8_t capacity = 0;
			uint8_t entryCount = 0;
			static const uint8_t entrySize = sizeof(uint32_t) + sizeof(DataType) + sizeof(Value);

			uint32_t* keys;
			DataType* type;
			Value* value;
		};

		//! Points to the next free spot in the value_buffer.
		struct Value_Buffer
		{
			size_t size = 0;
		};

		//! Struct for keeping track of the data entries an entity has been given.
		/*!
		The databuffer stores the header on the left side and the value_buffer on the right side.
		 When the buffers meet the size is increased.
		*/
		struct DataBuffer
		{
			void* data;
			size_t capacity; /*!< This capacity is in bytes!!! */ 

			EntryHeader header;
			Value_Buffer v_buffer;

			DataBuffer();
			~DataBuffer();

			//! Grow the entry buffer.
			const void Allocate(size_t size);

			//! Grow the entry buffer and copy the header immediately.
			const void AllocateAndResizeHeader(size_t size);

			//! Grow the header.
			const void HeaderResize();
		};

		//! The managers entity entry block.
		struct EntityData : public BaseManagerEntityEntryBlock
		{
			DataBuffer** dataBuff;/*!< Stores a pointer to the data entries for the entity entry */  
		};

		EntityData _entityEntires; /*!< A reference pointer to avoid having to cast the basic datapointer all the time. */

	public:
		DataManager(threadIdentifier identifier, uint8_t frameSyncTime = 16);
		~DataManager();


		const void Start();


	private:
		//! Register an entity entry
		const void _CreateData(const Entity& entity);



		///** Add the bool value to the given entity and key.
		//*
		//*/
		//const void AddBoolValue(const Entity& entity, const string& key, const bool val);
		///** Add the float value to the given entity and key.
		//*
		//*/
		//const void AddFloatValue(const Entity& entity, const string& key, const float val);
		///** Add the string value to the given entity and key.
		//*
		//*/
		//const void AddStringValue(const Entity& entity, const string& key, const string& val);



		///** Set the bool value to the given entity and key.
		//*
		//*/
		//const void SetBoolValue(const Entity& entity, const string& key, const bool val);
		///** Set the float value to the given entity and key.
		//*
		//*/
		//const void SetFloatValue(const Entity& entity, const string& key, const float val);
		///** Set the string value to the given entity and key.
		//*
		//*/
		//const void SetStringValue(const Entity& entity, const string& key, const string& val);



		///** Get the bool value to the given entity and key.
		//*
		//*/
		//bool GetBoolValue(const Entity& entity, const string& key, bool default_value);
		///** Get the float value to the given entity and key.
		//*
		//*/
		//float GetFloatValue(const Entity& entity, const string& key, float default_value);
		///** Get the string value to the given entity and key.
		//*
		//*/
		//string GetStringValue(const Entity& entity, const string& key, string default_value);


	private:
		//! Allocate more memory
		const void _Allocate(uint32_t size);

		//! Delete an entry in the memory block.
		/*!
		The deleted entry is replaced by the last in the block.
		*/
		const void _Destroy(uint32_t index);
	};




}
#endif