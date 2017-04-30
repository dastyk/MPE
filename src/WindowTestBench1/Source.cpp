
#if defined( DEBUG ) || defined( _DEBUG )
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
#endif

#define _P_MS

#include <Profiler.h>
#include <ConsoleThread.h>

#ifdef _DEBUG
#pragma comment(lib, "ProfilerD.lib")
#pragma comment(lib, "DebugConsoleD.lib")
#else
#pragma comment(lib, "Profiler.lib")
#pragma comment(lib, "DebugConsole.lib")
#endif

#include <EntitySystem\ScriptManager.h>
#include <ThreadMessageControl\ThreadMessageController.h>
#include <Renderer\Renderer.h>
#include <ResourceManager\ResourceManager.h>

#ifdef _DEBUG
#pragma comment(lib, "EntitySystemD.lib")
#pragma comment(lib, "RendererD.lib")
#pragma comment(lib, "ResourceManagerD.lib")
#else
#pragma comment(lib, "EntitySystem.lib")
#pragma comment(lib, "Renderer.lib")
#pragma comment(lib, "ResourceManager.lib")
#endif


#include <Windows.h>
#include <windowsx.h>

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
#if defined( DEBUG ) || defined( _DEBUG )
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//	_crtBreakAlloc = 220;
#endif
	DebugUtils::ConsoleThread::Init();
	DebugUtils::DebugConsole::Command_Structure exit =
	{
		nullptr,
		[](void* userData, int argc, char** argv)
	{
		MPE::ThreadMessageController::Send(nullptr, MPE::Destination::ThreadMessageController, MPE::Destination::ThreadMessageController, MPE::Tag::Shutdown);
	},
		"exit",
		"Send an exit message."
	};
	DebugUtils::ConsoleThread::AddCommand(&exit);
	DebugUtils::ConsoleThread::ShowConsole();

	StartProfile;
	std::vector<MPE::Thread*> threads;
	threads.push_back(new MPE::ResourceManager(nullptr, MPE::Destination::ResourceManager));
	threads.push_back(new MPE::ScriptManager(MPE::Destination::ScriptManager));
	threads.push_back(MPE::Renderer::CreateBackend(MPE::Renderer::Backend::DirectX11, MPE::Destination::Renderer));
	MPE::ThreadMessageController::Start(threads);

	DebugUtils::ConsoleThread::Shutdown();
	ProfileReturnConst(0);
}