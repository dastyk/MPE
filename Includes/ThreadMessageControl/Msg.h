#ifndef _MSG_H_
#define _MSG_H_
#pragma once
#include "Tag.h"
#include "Destination.h"
namespace MPE
{
	struct Msg
	{
		void* data;
		uint32_t src; /**< Source*/
		uint32_t tag; /**< Tag, if Tag::Any was specified. */
		uint8_t prio;
	};
	struct MsgComp
	{
		bool operator()(const Msg& lhs, const Msg& rhs) const
		{
			return lhs.prio >= rhs.prio;
		}
	};
}
#endif