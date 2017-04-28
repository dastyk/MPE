#ifndef _RENDERER_MESSAGES_H_
#define _RENDERER_MESSAGES_H_

#pragma once
#include <ThreadMessageControl\Tag.h>

namespace MPE
{
	namespace Tag
	{
		namespace Renderer
		{
			enum : uint64_t
			{
				RegisterScene = CreateTag(Destination::Renderer, 0),
				RegisterEntity = CreateTag(Destination::Renderer, 1),
				SetRenderScene = CreateTag(Destination::Renderer, 2)
			};
		};
	}
}
#endif