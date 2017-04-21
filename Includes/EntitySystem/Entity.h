#ifndef _ENTITY_H_
#define _ENTITY_H_

#pragma once
#include <stdint.h>

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
		//! Conversion to uint64_t
		operator const uint64_t() const { return ID; };
		const uint64_t ID;
	private:
		static const uint64_t GenerateID();

	};
}
#endif