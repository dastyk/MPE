#ifndef _WINDOW_H_
#define _WINDOW_H_

#pragma once
#include <Windows.h>
#include <stdint.h>

namespace MPE
{
	class Window
	{
	public:
		Window();
		~Window();

		HWND _hwnd;
		HINSTANCE _hInst;

		uint32_t _wWidth;
		uint32_t _wHeight;

		uint32_t _wPosX;
		uint32_t _wPosY;

		DWORD _style;

	};
}
#endif