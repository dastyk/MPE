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

	ThreadMessageController::ThreadMessageController()
	{


	}


	ThreadMessageController::~ThreadMessageController()
	{
		StartProfile;
		BroadC(nullptr, Src_ThreadMessageController, Tag::Shutdown);
		for (auto& t : _stdThreads)	
			t.join();
		ProfileReturnVoid;
	}
	const void ThreadMessageController::Init()
	{
		if (!_instance)
			_instance = new ThreadMessageController;
		return void();
	}
	const void ThreadMessageController::Shutdown()
	{
		delete _instance;
		_instance = nullptr;
		return void();
	}
	const void ThreadMessageController::StartThread(Thread * thread)
	{
		StartProfile;

		_instance->_stdThreads.push_back(std::move(std::thread(ThreadEntry, thread)));



		_instance->_threads[thread->GetIdentity()] = thread;



		ProfileReturnVoid;
	}

	const void ThreadMessageController::Send(void * data, uint32_t src, uint32_t dest, uint32_t tag, uint8_t prio)
	{
		StartProfile;
		auto& find = _instance->_threads.find(dest);
		if (find != _instance->_threads.end())
			find->second->Send(data, dest, tag, prio);

		ProfileReturnVoid;
	}

	const void ThreadMessageController::BroadC(void * data, uint32_t src, uint32_t tag, uint8_t prio)
	{
		StartProfile;
		for (auto& t : _instance->_threads)
			t.second->Send(data, src, tag, prio);
		ProfileReturnVoid;
	}

}