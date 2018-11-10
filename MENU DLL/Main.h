#pragma once
#include <iostream>
#include <windows.h>
#include <shlobj.h>
#include <exdisp.h>
#include <shlwapi.h>
#include <iostream>
#include <fstream>

#ifdef MENU_EXPORTS
	
#define MENUDLL_API __declspec(dllexport)

#else

#define MENUDLL_API __declspec(dllexport)
	
#endif // MENU_EXPORT



#ifdef __cpluscplus
extern "C"{
#endif

	MENUDLL_API void Run();

#ifdef __cpluscplus
}
#endif