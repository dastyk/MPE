#ifndef _MPE_TAG_H_
#define _MPE_TAG_H_
#pragma once
#include <stdint.h>

/** The basic tags used during message passing.*/
namespace MPE
{
	namespace Tag
	{
		static const uint32_t Any = 0;
		static const uint32_t Shutdown = 1;
	}
}

#endif