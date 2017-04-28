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
		\param src Intended src. Specify Destination::Any to accept message from any source
		\param tag An identifier for the recviever.
		\sa Tag
		\sa Destination
		*/
		const void Recv(Msg& msg, const Destination& src, const Tag& tag);

		//! Peek message queue 
		/*!
		This is a non-blocking command
		\sa Msg
		\param src Intended destination. Specify Destination::Any to accept message from any source
		\param tag An identifier for the recviever, tags are found in MPE::Tag, or any user defined tags
		\return Returns 0 if no messages in queue, non-zero otherwise.
		\sa Tag
		\sa Destination
		*/
		const uint32_t PeekMsg(Msg& msg, const Destination& src, const Tag& tag);
	public:

		virtual ~Thread();

		//! The main entry point for the thread.
		virtual const void Start() = 0;

		//! Get the identity of the thread.
		threadIdentifier GetIdentity()const { return _identity; };

		//! Recvieves message from other thread. 
		/*!
		This is a non-blocking command, will continue without wait for message to be delivered.
		This is called by other threads, not itself. For sending messages see ThreadMessageController::Send.
		\param data Data to be sent
		\param src Source of the message
		\param tag An identifier for the recviever.
		\param prio Priority of the message, 0 is lowest.
		\sa Tag
		\sa Destination
		*/
		const void Send(void* data, const Destination& src, const Tag& tag, uint8_t prio);

	};
}
#endif