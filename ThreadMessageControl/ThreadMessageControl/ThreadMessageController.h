#ifndef _THREAD_MESSAGE_CONTROLLER_H_
#define _THREAD_MESSAGE_CONTROLLER_H_
#pragma once
#include "Thread.h"
#include <stdint.h>
#include "MPE_Tag.h"
namespace MPE
{
	static uint32_t AnySrc;/* Specify to allow messages from any source. */

	/* The ThreadMessageController initiates threads and handles the communication between them. */
	class ThreadMessageController
	{
	public:
		ThreadMessageController();
		~ThreadMessageController();

		/* Starts a new thread */
		/* thread: Pointer to the class which should occupy the thread*/
		/* frameSyncTime: Limit the thread's frametime to a specific time.*/
		const void StartThread(Thread* thread, /*Allocator info,*/double frameSyncTime);

		/* Send a message */
		/* This is a non-blocking command */
		/* data: Data to be sent */
		/* size: size of data */
		/* dest: Intended destination */
		/* tag: An identifier for the recviever, tags are found in MPE::Tag, or any user defined tags */
		const void Send(void* data, size_t size, uint32_t dest, uint32_t tag);

		/* Send a Broadcast to all threads */
		/* This is a non-blocking command */
		/* data: Data to be sent */
		/* size: size of data */
		/* tag: An identifier for the recviever, tags are found in MPE::Tag, or any user defined tags */
		const void BroadC(void* data, size_t, uint32_t tag);

		/* Recvieve a message */
		/* This is a blocking command */
		/* data: Data will be initialized and filled with recvieved data*/
		/* size: size of data */
		/* Src: Intended destination. Specify MPE::AnySrc to accept message from any source */
		/* tag: An identifier for the recviever, tags are found in MPE::Tag, or any user defined tags */
		const void Recv(void** data, size_t& size, uint32_t src, uint32_t tag);

		/* Peek message queue */
		/* This is a non-blocking command */
		/* data: Data will be initialized and filled with recvieved data*/
		/* size: size of data */
		/* Src: Intended destination. Specify MPE::AnySrc to accept message from any source */
		/* tag: An identifier for the recviever, tags are found in MPE::Tag, or any user defined tags */
		/* return: Returns 0 if no messages in queue, non-zero otherwise. */
		const uint32_t PeekMsg(void** data, size_t& size, uint32_t src, uint32_t tag);
	};
}


#endif