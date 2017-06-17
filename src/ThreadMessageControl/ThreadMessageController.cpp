#include "ThreadMessageController.h"
#include <MemoryLeakDetection.h>
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

		for (auto& t : threadsToStart)
		{
			_threads[t->GetIdentity()] = t;

		}
		

	}


	ThreadMessageController::~ThreadMessageController()
	{
		StartProfile;
		BroadCast(nullptr, Destination::ThreadMessageController, Tag::Shutdown);
		for (auto& t : _stdThreads)
			t.join();


		for (auto& t : _threads)
			delete t.second;
		ProfileReturnVoid;
	}
	const void ThreadMessageController::Start(const std::vector<Thread*>& threadsToStart, uint8_t frameSyncTime)
	{
		if (!_instance)
			_instance = DBG_NEW ThreadMessageController(threadsToStart, frameSyncTime);

		_instance->Start();
		return void();
	}
	const void ThreadMessageController::Start()
	{
		Msg msg;
		bool running = true;

		for (auto& t : _threads)
		{
			_stdThreads.push_back(std::move(std::thread(ThreadEntry, t.second)));

		}
		_threads[Destination::ThreadMessageController] = this;
		while (running)
		{
			StartProfile;


			if (PeekMsg(msg))
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
		//if (dest == 0)
		//{
		//	_instance->_threads[0]->Send(data, src, tag, prio);
		//	return;
		//}
		for (uint8_t i = 0; i < 32; i++)
		{
			auto d = dest & 1 << i;
			if (d)
			{
				auto& find = _instance->_threads.find(d);
				if (find != _instance->_threads.end())
					find->second->Send(data, src, tag, prio);
			}
		}
		

		ProfileReturnVoid;
	}

	const void ThreadMessageController::BroadCast(void * data, uint32_t src, uint64_t tag, uint8_t prio)
	{
		StartProfile;
		for (auto& t : _instance->_threads)
			t.second->Send(data, src, tag, prio);
		ProfileReturnVoid;
	}

}