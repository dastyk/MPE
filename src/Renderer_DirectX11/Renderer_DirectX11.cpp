#include "Renderer_DirectX11.h"

#include <Profiler.h>

#ifdef _DEBUG
#pragma comment(lib, "ProfilerD.lib")
#else
#pragma comment(lib, "Profiler.lib")
#endif

namespace MPE
{
	Renderer_DirectX11::Renderer_DirectX11(threadIdentifier identifier, uint8_t frameSyncTime) : Renderer(identifier, frameSyncTime), _window(), _d3d()
	{
		StartProfile;
		_d3d.Start(_window._hwnd, _window._wWidth, _window._wHeight);
		StopProfile;
	}


	Renderer_DirectX11::~Renderer_DirectX11()
	{
		_d3d.Shutdown();
	}
	const void Renderer_DirectX11::Start()
	{
		Msg msg;
		bool running = true;
		while (running)
		{
			StartProfile;


			if (PeekMsg(msg, Msg::Destination::Any, Msg::Tag::Any))
			{
				if (msg.tag == Msg::Tag::Shutdown)
					running = false;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(_frameSyncTime));

			StopProfile;
		}

	}
}