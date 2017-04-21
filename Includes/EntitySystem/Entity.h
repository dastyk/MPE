#ifndef _ENTITY_H_
#define _ENTITY_H_

#pragma once
#include <stdint.h>
#include <functional>

namespace MPE
{ 
	//!  Entity is essentially an id
	struct Entity
	{
		//! Creates the entity
		/*!
			A random 64bit integer is generated as ID. 
			It is highly unlikely we will get the same ID.
		*/		
		Entity() : ID(GenerateID()) {};

		//! Creates the entity with a specified ID.
		Entity(const uint64_t ID) : ID(ID) {};

		//! Conversion to uint64_t
		operator const uint64_t() const { return ID; };

		const Entity& operator=(const uint64_t& other) { this->ID = other; return *this; }
		const Entity& operator=(const Entity& other) { this->ID = other.ID; return *this; }
		const bool operator==(const Entity& other)const { return this->ID == other.ID; }


		uint64_t ID;

	private:
		static const uint64_t GenerateID();

	};

	struct EntityHasher
	{
		size_t operator()(const Entity& key) const
		{
			return std::hash<uint64_t>()(key.ID);
		}
	};
}
#endif