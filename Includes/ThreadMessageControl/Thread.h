#ifndef _THREAD_H_
#define _THREAD_H_
#pragma once

namespace MPE
{
	//! The thread base class
	/*!
		This is a pure virtual class and is intended to be inherited by classes that wishes to use the ThreadMessageController.
		\sa ThreadMessageController
	*/
	class Thread
	{
	protected:
		Thread();
		virtual ~Thread();
	};
}
#endif