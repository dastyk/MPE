#pragma once
// debug_new.cpp
// compile by using: cl /EHsc /W4 /D_DEBUG /MDd debug_new.cpp
#if defined( DEBUG ) || defined( _DEBUG )
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#define MLD_INIT {\
_CrtDumpMemoryLeaks();\
_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);\
_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);\
 }


//	_crtBreakAlloc = 220;

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define MLD_INIT
#define DBG_NEW new
#endif
