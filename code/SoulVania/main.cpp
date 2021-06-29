#include "stdafx.h"
#include "TestGame.h"
#include "CastlevaniaGame.h"

#if _WIN32
// Prefer the high-performance GPU on switchable GPU systems
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 1;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

#pragma comment( lib, "winmm.lib" )
#endif

int main()
{
	//TestGame{}.Run();
	CastlevaniaGame{}.Run();
}