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

	ThreadMessageController::ThreadMessageController(const std::vector<Thread*>& threadsToStart, uint8_t frameSyncTime) : Thread(Destination::ThreadMessageController, frameSyncTime)
	{
		_threads[Destination::ThreadMessageController] = this;
		for (auto& t : threadsToStart)
		{
			_threads[t->GetIdentity()] = t;
			
		}
		for (auto& t : threadsToStart)
		{
			_stdThreads.push_back(std::move(std::thread(ThreadEntry, t)));

		}
		
	}


	ThreadMessageController::~ThreadMessageController()
	{
		StartProfile;
		BroadC(nullptr, Destination::ThreadMessageController, Tag::Shutdown);
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


			if (PeekMsg(msg, Destination::Any, Tag::Any))
			{
				if (msg.tag == Tag::Shutdown)
					running = false;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(_frameSyncTime));
			StopProfile;
		}
		_threads.erase(Destination::ThreadMessageController);
		delete this;
	}


	const void ThreadMessageController::Send(void * data, uint32_t src, uint32_t dest, uint64_t tag, uint8_t prio)
	{
		StartProfile;
		auto& find = _instance->_threads.find(dest);
		if (find != _instance->_threads.end())
			find->second->Send(data, dest, tag, prio);

		ProfileReturnVoid;
	}

	const void ThreadMessageController::BroadC(void * data, uint32_t src, uint64_t tag, uint8_t prio)
	{
		StartProfile;
		for (auto& t : _instance->_threads)
			t.second->Send(data, src, tag, prio);
		ProfileReturnVoid;
	}

}