#ifndef _THREAD_MESSAGE_CONTROLLER_H_
#define _THREAD_MESSAGE_CONTROLLER_H_
#pragma once
#include "Thread.h"
#include <stdint.h>
#include "MPE_Tag.h"
namespace MPE
{
	static uint32_t AnySrc;/**< Specify to allow messages from any source. */

	//! The ThreadMessageController initiates threads and handles the communication between them. 
	class ThreadMessageController
	{
	public:
		ThreadMessageController();
		~ThreadMessageController();

		 //! Starts a new thread. 
		 /*!
		 \param thread: Pointer to the class which should occupy the thread
		 \param frameSyncTime: Limit the thread's frametime to a specific time.
		 \sa Thread
		 */
		const void StartThread(Thread* thread, /*Allocator info,*/double frameSyncTime);

		//! \brief Send a message. 
		/*!
		  This is a non-blocking command 
		 \param data: Data to be sent 
		 \param size: size of data 
		 \param dest: Intended destination 
		 \param tag: An identifier for the recviever.
		 \sa Tag
		 */
		const void Send(void* data, size_t size, uint32_t dest, uint32_t tag);

		//! \brief Send a Broadcast to all threads. 
		/*!
		  This is a non-blocking command 
		\param  data: Data to be sent 
		\param size: size of data 
		\param  tag: An identifier for the recviever. 
		\sa Tag
		*/
		const void BroadC(void* data, size_t, uint32_t tag);

		//! \brief Recvieve a message
		/*!
		  This is a blocking command 
		 \param data: Data will be initialized and filled with recvieved data
		 \param size: size of data
		 \param Src: Intended destination. Specify MPE::AnySrc to accept message from any source
		 \param tag: An identifier for the recviever.
		 \sa Tag
		 */
		const void Recv(void** data, size_t& size, uint32_t src, uint32_t tag);

		 //! \brief Peek message queue 
		 /*!
		  This is a non-blocking command 
		 \param data: Data will be initialized and filled with recvieved data
		 \param size: size of data 
		 \param Src: Intended destination. Specify MPE::AnySrc to accept message from any source 
		 \param tag: An identifier for the recviever, tags are found in MPE::Tag, or any user defined tags 
		 \return Returns 0 if no messages in queue, non-zero otherwise. 
		 \sa Tag
		 */
		const uint32_t PeekMsg(void** data, size_t& size, uint32_t src, uint32_t tag);
	};
}


#endif