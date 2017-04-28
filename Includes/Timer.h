#ifndef _TIMER_H_
#define _TIMER_H_

#pragma once

#include <chrono>

namespace MPE
{
	class Timer
	{
	public:
		Timer() {}
		~Timer() {}

		const void Start()
		{
			_timeDelta = _timeStart = std::chrono::high_resolution_clock::now();
		}

		template<class T = std::chrono::seconds>
		const T Total()
		{
			auto timEnd = std::chrono::high_resolution_clock::now();
			return std::chrono::duration_cast<T>(timEnd - _timeStart);
		}
		const void Reset()
		{
			_timeDelta = _timeStart = std::chrono::high_resolution_clock::now();
		}
		template<class T = std::chrono::seconds>
		const T GetDelta()
		{
			auto now = std::chrono::high_resolution_clock::now();
			auto diff = now - _timeDelta;
			_timeDelta = now;
			return std::chrono::duration_cast<T>(diff);
		}

	private:
		std::chrono::high_resolution_clock::time_point _timeStart;
		std::chrono::high_resolution_clock::time_point _timeDelta;

	};
}
#endif