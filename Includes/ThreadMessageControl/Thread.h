#ifndef _THREAD_H_
#define _THREAD_H_
#pragma once
#include <stdint.h>
#include <thread>
#include <queue>
#include "Msg.h"
#include <mutex>

namespace MPE
{
	typedef uint32_t threadIdentifier;
	//! The thread base class
	/*!
		This is a virtual class and is intended to be inherited by classes that wishes to use the ThreadMessageController.
		\sa ThreadMessageController
	*/
	class Thread
	{
	protected:
		
		//! Thread contructor
		/*!
		\param frameSyncTime: Limit the thread's frametime to a specific time in ms.
		*/
		Thread(threadIdentifier identifier, uint8_t frameSyncTime = 16);
		virtual ~Thread();

		threadIdentifier _identity;
		uint8_t _frameSyncTime;


		std::priority_queue<Msg, std::vector<Msg>, MsgComp> _messageQueue;


	private:
		std::mutex _writeLock;
	protected:
	
		//! Recvieve a message
		/*!
		This is a blocking command.
		Waits for a specific message.
		\sa Msg
		\param Src: Intended src. Specify MPE::Msg_Any_Src to accept message from any source
		\param tag: An identifier for the recviever.
		\sa Tag
		*/
		const void Recv(Msg& msg, uint32_t src, uint32_t tag);

		//! Peek message queue 
		/*!
		This is a non-blocking command
		\sa Msg
		\param Src: Intended destination. Specify MPE::Msg_Any_Src to accept message from any source
		\param tag: An identifier for the recviever, tags are found in MPE::Tag, or any user defined tags
		\return Returns 0 if no messages in queue, non-zero otherwise.
		\sa Tag
		*/
		const uint32_t PeekMsg(Msg& msg, uint32_t src, uint32_t tag);
	public:
		//! The main entry point for the thread.
		virtual const void Start() = 0;

		threadIdentifier GetIdentity()const { return _identity; };

		//! Recvieves message from other thread. 
		/*!
		This is a non-blocking command, will continue without wait for message to be delivered.
		This is called by other threads, not itself. For sending messages see ThreadMessageController::Send.
		\param data: Data to be sent
		\param src: Source
		\param tag: An identifier for the recviever.
		\param prio: Priority of the message, 0 is lowest.
		\sa Tag
		*/
		const void Send(void* data, uint32_t src, uint32_t tag, uint8_t prio);

	};
}
#endif