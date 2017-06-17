
#include <MemoryLeakDetection.h>
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
#include <ResourceManager\ResoureManagerMessages.h>
#include <ResourceManager\RawAssetLoader.h>

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
	MLD_INIT;
	DebugUtils::ConsoleThread::Init();
	DebugUtils::DebugConsole::Command_Structure exit =
	{
		nullptr,
		[](void* userData, int argc, char** argv)
	{
		MPE::ThreadMessageController::BroadCast(nullptr, MPE::Destination::ThreadMessageController, MPE::Tag::Shutdown);
	},
		"exit",
		"Send an exit message."
	};
	DebugUtils::ConsoleThread::AddCommand(&exit);

	DebugUtils::DebugConsole::Command_Structure msg =
	{
		nullptr,
		[](void* userData, int argc, char** argv)
	{
		auto help = [](){
			printf("msg [target, message] \t --- \t Send a message to a thread.\n");
			for (int i = 0;i < 40; i++) printf("*");
			printf("\n\t Target: ResourceManager\n");
			printf("\t\t LoadResource [filename, <priority>]\n");
		};
		if (argc < 3)
		{
			help();
			return;
		}

		std::string target = argv[1];
		std::string message = argv[2];
		if (target == "ResourceManager")
		{
			if (message == "LoadResource")
			{
				if (argc < 4)
				{
					help();
					return;
				}
				uint8_t prio = 0;
				if (argc > 4)
					prio = std::stoi(argv[4]);
				MPE::ThreadMessageController::Send(MPE::Tag::ResourceManager::LoadResourceStruct::Create(MPE::GUID(argv[3]),0), MPE::Destination::ThreadMessageController, MPE::Destination::ResourceManager, MPE::Tag::ResourceManager::LoadResource, prio);
			}
		}

	},
		"msg",
		"Send a message."
	};
	DebugUtils::ConsoleThread::AddCommand(&msg);
	DebugUtils::ConsoleThread::ShowConsole();

	StartProfile;
	std::vector<MPE::Thread*> threads;
	threads.push_back(DBG_NEW MPE::ResourceManager(MPE::Destination::ResourceManager));
	threads.push_back(DBG_NEW MPE::ScriptManager(MPE::Destination::ScriptManager));
	threads.push_back(MPE::Renderer::CreateBackend(MPE::Renderer::Backend::DirectX11, MPE::Destination::Renderer));
	MPE::ThreadMessageController::Start(threads);

	DebugUtils::ConsoleThread::Shutdown();
	ProfileReturnConst(0);
}