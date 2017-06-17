#include "Thread.h"
#include <Profiler.h>

#ifdef _DEBUG
#pragma comment(lib, "ProfilerD.lib")
#else
#pragma comment(lib, "Profiler.lib")
#endif

namespace MPE
{

	Thread::Thread(threadIdentifier identifier, uint8_t frameSyncTime) : _frameSyncTime(frameSyncTime), _identity(identifier)
	{

	}


	Thread::~Thread()
	{
	}
	const uint32_t Thread::PeekMsg(Msg & msg)
	{
		StartProfile;
		
		if (_messageQueue.size() == 0)
			ProfileReturnConst(0);

		/*if(!_writeLock.try_lock())
			ProfileReturnConst(0);*/

		_writeLock.lock();

		auto ret = _messageQueue.size();
		msg = _messageQueue.top();
		_messageQueue.pop();

		_writeLock.unlock();
		ProfileReturn(ret);
	}
	const void Thread::Send(void * data, uint32_t src, uint64_t tag, uint8_t prio)
	{
		StartProfile;
		_writeLock.lock();
		_messageQueue.push({ data, src, tag, prio });
		_writeLock.unlock();
		ProfileReturnVoid;
	}
}