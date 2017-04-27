#ifndef _RENDERER_H_
#define _RENDERER_H_
#pragma once
#include <stdint.h>
#include <ThreadMessageControl\Thread.h>

#ifdef _DEBUG
#pragma comment(lib, "ThreadMessageControlD.lib")
#else
#pragma comment(lib, "ThreadMessageControl.lib")
#endif


namespace MPE
{
	
	class Renderer : public Thread
	{
	public:
		enum class Backend : uint8_t
		{
			DirectX11
		};

	protected:
		Renderer(threadIdentifier identifier, uint8_t frameSyncTime = 16);
	public:
		static Renderer* CreateBackend(Backend backend, threadIdentifier identifier, uint8_t frameSyncTime = 16);
		~Renderer();
	};
}

#endif