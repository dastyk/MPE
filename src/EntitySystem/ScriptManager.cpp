#include "ScriptManager.h"

#include <Profiler.h>
#include <DataManager.h>

#ifdef _DEBUG
#pragma comment(lib, "ProfilerD.lib")
#else
#pragma comment(lib, "Profiler.lib")
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
	
		if (!_state.Load("data.lua"))
		{
			printf("Script error\n");
			return;
		}

		_state["Entity"].SetClass<EntityProxy>("Test2", &EntityProxy::Test2);
		//_state["Scene"].SetClass<SceneProxy>("AddEntity", &SceneProxy::AddEntity);//,"Clear", &SceneProxy::Clear);
		//_state["Scene"].SetClass<SceneProxy>("Clear", &SceneProxy::Clear);

		_state["AddScene"] = [this](sel::Reference<SceneProxy> scene) {this->CreateScene(scene);};
		_state["main"]();

		Msg msg;
		bool running = true;
		while (running)
		{
			StartProfile;


			if (PeekMsg(msg, Destination::Any, Tag::Any))
			{
				if (msg.tag == Tag::Shutdown)
					running = false;


				std::this_thread::sleep_for(std::chrono::milliseconds(_frameSyncTime));

				StopProfile;
			}

			return void();
		}
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