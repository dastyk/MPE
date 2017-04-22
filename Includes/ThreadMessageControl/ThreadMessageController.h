#ifndef _THREAD_MESSAGE_CONTROLLER_H_
#define _THREAD_MESSAGE_CONTROLLER_H_
#pragma once
#include "Thread.h"
#include <stdint.h>
#include "MPE_Tag.h"
#include <unordered_map>

namespace MPE
{

	//! The ThreadMessageController initiates threads.
	class ThreadMessageController
	{
	private:
		std::vector<std::thread> _stdThreads;
		std::unordered_map<threadIdentifier, Thread*> _threads;


		static ThreadMessageController* _instance;

		ThreadMessageController();
		~ThreadMessageController();
	public:
		static const void Init();
		static const void Shutdown();



		 //! Starts a new thread. 
		 /*!
		 \param thread: Pointer to the class which should occupy the thread
		 \sa Thread
		 */
		static const void StartThread(Thread* thread /*Allocator info,*/);

		//! Send a message. 
		/*!
		  This is a non-blocking command 
		 \param data: Data to be sent 
		 \param src: From where the message is sent.
		 \param dest: Intended destination 
		 \param tag: An identifier for the recviever.
		 \sa Tag
		 */
		static const void Send(void* data, uint32_t src, uint32_t dest, uint32_t tag, uint8_t prio = 0);

		//! Send a Broadcast to all threads. 
		/*!
		  This is a non-blocking command 
		\param  data: Data to be sent 
		\param src: From where the message is sent.
		\param  tag: An identifier for the recviever. 
		\param prio: Priority of the message, 0 is lowest.
		\sa Tag
		*/
		static const void BroadC(void* data, uint32_t src, uint32_t tag, uint8_t prio = UINT8_MAX);
	};
}


#endif