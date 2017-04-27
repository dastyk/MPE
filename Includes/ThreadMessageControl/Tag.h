#ifndef _TAG_H_
#define _TAG_H_
#pragma once
#include <stdint.h>

/** The basic tags used during message passing.*/
namespace MPE
{
	namespace Tag
	{
		const static uint32_t Any = 0;
		const static uint32_t Shutdown = 1;
	}
}

#endif