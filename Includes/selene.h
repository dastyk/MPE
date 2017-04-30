#pragma once

#if defined(_MSC_VER) && _MSC_VER < 1900 // before MSVS-14 CTP1
#define constexpr const
#endif

#ifdef _DEBUG
#pragma comment(lib, "LuaD.lib")
#else
#pragma comment(lib, "Lua.lib")
#endif

#include "selene/State.h"
#include "selene/Tuple.h"
