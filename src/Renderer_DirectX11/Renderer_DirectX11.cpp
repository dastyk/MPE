#include "Renderer_DirectX11.h"

#include <Profiler.h>

#ifdef _DEBUG
#pragma comment(lib, "ProfilerD.lib")
#else
#pragma comment(lib, "Profiler.lib")
#endif

namespace MPE
{
	Renderer_DirectX11::Renderer_DirectX11(threadIdentifier identifier, uint8_t frameSyncTime) : Renderer(identifier, frameSyncTime), _d3d()
	{
		auto hwnd = GetActiveWindow();
		RECT r;
		GetClientRect(hwnd, &r);
		_d3d.Start(hwnd, r.right, r.bottom);
	}


	Renderer_DirectX11::~Renderer_DirectX11()
	{
	}
	const void Renderer_DirectX11::Start()
	{
		Msg msg;
		bool running = true;
		while (running)
		{
			StartProfile;


			if (PeekMsg(msg, Destination::Any, Tag::Any))
			{
				if (msg.tag == Tag::Shutdown)
					running = false;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(_frameSyncTime));

			StopProfile;
		}

	}
}