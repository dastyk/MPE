#include "ScriptManager.h"

#include <Profiler.h>
#include <DataManager.h>
#include <fstream>
#include <Timer.h>
#include <ThreadMessageControl\ThreadMessageController.h>
#include <ResourceManager\ResoureManagerMessages.h>
#ifdef _DEBUG
#pragma comment(lib, "ProfilerD.lib")
#pragma comment(lib, "ThreadMessageControlD.lib")
#else
#pragma comment(lib, "Profiler.lib")
#pragma comment(lib, "ThreadMessageControl.lib")
#endif



namespace MPE
{
	ScriptManager::ScriptManager(threadIdentifier identifier, uint8_t frameSyncTime) : Thread(identifier, frameSyncTime), _state()
	{
		_state.HandleExceptionsPrintingToStdOut();
	}


	ScriptManager::~ScriptManager()
	{
	}

	const void ScriptManager::Start()
	{

		//std::ifstream file;
		//file.open("data.lua");
		//if (!file.is_open())
		//{
		//	printf("Script file data.lua could not be found.");
		//	return;
		//}
		//if (!_state.Load("data.lua"))
		//{
		//	printf("Script error\n");
		//	return;
		//}

		//_state["Entity"].SetClass<EntityProxy>("Test2", &EntityProxy::Test2);
		////_state["Scene"].SetClass<SceneProxy>("AddEntity", &SceneProxy::AddEntity);//,"Clear", &SceneProxy::Clear);
		////_state["Scene"].SetClass<SceneProxy>("Clear", &SceneProxy::Clear);

		//_state["AddScene"] = [this](sel::Reference<SceneProxy> scene) {this->CreateScene(scene);};
		//_state["main"]();

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
				if (msg.tag == Tag::ResourceManager::LoadResourceResponse)
				{
					auto& r = *(Tag::ResourceManager::ResouceData*)msg.data;
					int i = r.tag;
					printf("data.lua contains: %s", r.data);
				}

				msg.Clean();
			}

			// Sync with frametime. // TODO: Make sure everything work even if frame took more than frametime.
			auto time = timer.Total<std::chrono::milliseconds>();
			std::this_thread::sleep_for(std::chrono::milliseconds(_frameSyncTime) - time);
			timer.Reset();




			// Do general work.
			static bool f = true;
			if (f)
			{
				ThreadMessageController::Send(Tag::ResourceManager::LoadResourceStruct::Create("data.lua", 1), Destination::ScriptManager, Destination::ResourceManager, Tag::ResourceManager::LoadResource);
				f = false;
			}



			StopProfile;
			
		}
		return void();
	}
	const void ScriptManager::RegisterManager(Manager * manager)
	{
		_entityManagers.push_back(manager);
	}
	const void ScriptManager::RegisterManager(const std::vector<Manager*>& managers)
	{
		_entityManagers.insert(_entityManagers.end(), managers.begin(), managers.end());
		return void();
	}
	void ScriptManager::CreateScene(sel::Reference<SceneProxy> scene)
	{
		SceneProxy s = scene;
		int i = 0;
		return void();
	}
}