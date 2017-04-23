#ifndef _MSG_H_
#define _MSG_H_
#pragma once
#include "Tag.h"
namespace MPE
{
	static uint32_t Src_ThreadMessageController = 0; /**< Soruce 0 is reserved for ThreadMessageController. */
	static uint32_t Msg_Any_Src = UINT32_MAX;/**< Specify to allow messages from any source. */
	struct Msg
	{
		void* data;
		uint32_t src; /**< Source, if Msg_Any_Src was specified. */
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