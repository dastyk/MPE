#include "Renderer.h"
#include <Renderer_DirectX11\Renderer_DirectX11.h>
#include <MemoryLeakDetection.h>
#ifdef _DEBUG
#pragma comment(lib, "Renderer_DirectX11D.lib")
#else
#pragma comment(lib, "Renderer_DirectX11.lib")
#endif

namespace MPE
{
	Renderer::Renderer(threadIdentifier identifier, uint8_t frameSyncTime) : Thread(identifier, frameSyncTime)
	{
	}
	Renderer* Renderer::CreateBackend(Backend backend, threadIdentifier identifier, uint8_t frameSyncTime)
	{
		switch (backend)
		{
		case Backend::DirectX11:
			return DBG_NEW Renderer_DirectX11(identifier, frameSyncTime);
			break;
		default:
			break;
		}
	}
	Renderer::~Renderer()
	{
	}
}