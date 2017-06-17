#include "Renderer_DirectX11.h"

#include <Profiler.h>

#ifdef _DEBUG
#pragma comment(lib, "ProfilerD.lib")
#else
#pragma comment(lib, "Profiler.lib")
#endif
#include <Timer.h>

#include <Renderer\RendererMessages.h>

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
		Timer timer;
		Msg msg;
		bool running = true;
		timer.Start();
		while (running)
		{
			StartProfile;


			while (timer.Total<std::chrono::milliseconds>().count() < _frameSyncTime && PeekMsg(msg))
			{
				if (msg.tag == Tag::Shutdown)
					running = false;
			}

			auto time = timer.Total<std::chrono::milliseconds>();

			std::this_thread::sleep_for(std::chrono::milliseconds(_frameSyncTime) - time);
			timer.Reset();

			StopProfile;
		}

	}
}