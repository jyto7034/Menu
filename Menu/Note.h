#pragma once
#pragma once
#include <iostream>
#include <windows.h>
#include <shlobj.h>
#include <exdisp.h>
#include <shlwapi.h>
#include <iostream>
#include <fstream>

#ifdef MENU_EXPORT

#define MENU_API __declspec(dllimport)

#else

#define MENU_API __declspec(dllimport)

#endif // MENU_EXPORT



#ifdef __cplusplus

#define EXTERN_C					extern "C"
#define EXTERN_C_START	extern "C"{
#define EXTERN_C_END	}

#else

#define EXTERN_C					extern "C"
#define EXTERN_C_START	extern "C"{
#define EXTERN_C_END	}

#endif // __cplusplus




EXTERN_C_START

int APIENTRY MENU_API _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow);
LRESULT CALLBACK MENU_API _stdcall WndProc(HWND, UINT, WPARAM, LPARAM);
void Detect(HWND hwnd, UINT, UINT_PTR, DWORD);
//void MENU_API _stdcall F_CreateWindow(HINSTANCE hInstance, HWND hWnd, int nCmdShow);

EXTERN_C_END