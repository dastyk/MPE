#include "ThreadMessageController.h"

#include <Profiler.h>

#ifdef _DEBUG
#pragma comment(lib, "ProfilerD.lib")
#else
#pragma comment(lib, "Profiler.lib")
#endif


namespace MPE
{

	ThreadMessageController* ThreadMessageController::_instance = nullptr;

	const void ThreadEntry(Thread* thread)
	{
		thread->Start();
	}

	ThreadMessageController::ThreadMessageController(const std::vector<Thread*>& threadsToStart, uint8_t frameSyncTime) : Thread(Msg::Destination::ThreadMessageController, frameSyncTime)
	{

		for (auto& t : threadsToStart)
		{
			_threads[t->GetIdentity()] = t;
			_stdThreads.push_back(std::move(std::thread(ThreadEntry, t)));
		}


	}


	ThreadMessageController::~ThreadMessageController()
	{
		StartProfile;
		BroadC(nullptr, Msg::Destination::ThreadMessageController, Msg::Tag::Shutdown);
		for (auto& t : _stdThreads)	
			t.join();


		for (auto& t : _threads)
			delete t.second;
		ProfileReturnVoid;
	}
	const void ThreadMessageController::Start(const std::vector<Thread*>& threadsToStart, uint8_t frameSyncTime)
	{
		if (!_instance)
			_instance = new ThreadMessageController(threadsToStart, frameSyncTime);

		_instance->Start();
		return void();
	}
	const void ThreadMessageController::Start()
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

			std::this_thread::sleep_for(std::chrono::seconds(2));//std::chrono::milliseconds(_frameSyncTime));
			running = false;
			StopProfile;
		}

		delete this;
	}


	const void ThreadMessageController::Send(void * data, const Msg::Destination& src, const Msg::Destination& dest, const Msg::Tag& tag, uint8_t prio)
	{
		StartProfile;
		auto& find = _instance->_threads.find(dest);
		if (find != _instance->_threads.end())
			find->second->Send(data, dest, tag, prio);

		ProfileReturnVoid;
	}

	const void ThreadMessageController::BroadC(void * data, const Msg::Destination& src, const Msg::Tag& tag, uint8_t prio)
	{
		StartProfile;
		for (auto& t : _instance->_threads)
			t.second->Send(data, src, tag, prio);
		ProfileReturnVoid;
	}

}