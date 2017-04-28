#ifndef _DATA_MANAGER_MESSAGES_H_
#define _DATA_MANAGER_MESSAGES_H_

#pragma once
#include <ThreadMessageControl\Tag.h>
namespace MPE
{
	namespace Tag
	{
		//! The tags used in the DataManager
		namespace DataManager
		{
			enum : uint64_t
			{
				RegisterEntity = CreateTag(Destination::DataManager, 0),
			};
		};
	}
}
#endif