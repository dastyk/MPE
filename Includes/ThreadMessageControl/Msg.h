#ifndef _MSG_H_
#define _MSG_H_
#pragma once


#include "Destination.h"
#include "Tag.h"
namespace MPE
{
	struct Msg
	{
		void* data; /**< Must be created with new */
		uint32_t src; /**< Who the message if from. */
		uint64_t tag; /**< Tag, if Tag::Any was specified. */
		uint8_t prio;

		const void Clean()
		{
			operator delete(data);
			data = nullptr;
		}
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