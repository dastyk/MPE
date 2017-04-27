#include "Window.h"
#include <stdexcept>
#include <Profiler.h>

#ifdef _DEBUG
#pragma comment(lib, "ProfilerD.lib")
#else
#pragma comment(lib, "Profiler.lib")
#endif
namespace MPE
{
	Window::Window()
	{
		StartProfile;
		// Setup the windows class
		WNDCLASSEX wc;
		_hInst = GetModuleHandle(NULL);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = DefWindowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = _hInst;
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = "Wind";
		wc.cbSize = sizeof(WNDCLASSEX);


		_wWidth = 800;
		_wHeight = 640;


		// Register the window class.
		//Place the window in the middle of the Window.
		_wPosX = (GetSystemMetrics(SM_CXSCREEN) - (int)_wWidth) / 2;
		_wPosY = (GetSystemMetrics(SM_CYSCREEN) - (int)_wHeight) / 2;

		RegisterClassEx(&wc);
		RECT rc = { 0, 0, (LONG)_wWidth, (LONG)_wHeight };

		AdjustWindowRect(&rc, _style, FALSE);
		// Create the window with the Window settings and get the handle to it.
		_hwnd = CreateWindowEx(
			WS_EX_APPWINDOW,
			"Wind",
			"Wind",
			_style,
			_wPosX,
			_wPosY,
			rc.right - rc.left,
			rc.bottom - rc.top,
			NULL,
			NULL,
			_hInst,
			NULL);
		if (!_hwnd)
		{
			throw std::runtime_error("Failed to create Window");
		}

		//if (fullscreen)
		//{
		//	SetWindowLongPtr(_hWnd, GWL_STYLE,
		//		WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE);

		//	_windowPosX = 0;
		//	_windowPosY = 0;
		//	windowWidth = (LONG)GetSystemMetrics(SM_CXSCREEN);
		//	windowHeight = (LONG)GetSystemMetrics(SM_CYSCREEN);
		//	SetWindowPos(_hWnd, 0, _windowPosX, _windowPosY, windowWidth, windowHeight, SWP_SHOWWINDOW);
		//	SetForegroundWindow(_hWnd);
		//	SetFocus(_hWnd);


		//	DEVMODE dmWindowSettings;
		//	// If full Window set the Window to maximum size of the users desktop and 32bit.
		//	memset(&dmWindowSettings, 0, sizeof(dmWindowSettings));
		//	dmWindowSettings.dmSize = sizeof(dmWindowSettings);
		//	dmWindowSettings.dmPelsWidth = (unsigned long)windowWidth;
		//	dmWindowSettings.dmPelsHeight = (unsigned long)windowHeight;
		//	dmWindowSettings.dmBitsPerPel = 32;
		//	dmWindowSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//	int r = ChangeDisplaySettings(&dmWindowSettings, 0) == DISP_CHANGE_SUCCESSFUL;

		//	System::GetInput()->LockMouseToWindow(true);
		//}

		// Bring the window up on the Window and set it as main focus.
		ShowWindow(_hwnd, SW_SHOW);
		SetForegroundWindow(_hwnd);
		SetFocus(_hwnd);

		// Set the cursor to the middle of the client window
		SetCursorPos(_wPosX + _wWidth / 2, _wPosY + _wHeight / 2);
		StopProfile;
	}

	Window::~Window()
	{
	}
}