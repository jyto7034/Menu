//#include <windows.h>
//#include <shlobj.h>
//#include <exdisp.h>
//#include <shlwapi.h>
//#include <iostream>
////#include <Python.h>		
//
//
//#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
//#pragma comment(lib, "Shlwapi.lib")
//
//using namespace std;
//
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//HINSTANCE g_hInst;
//LPCWSTR lpszClass = TEXT("TextOut");
//
//BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpcs);
//void CALLBACK Detect(HWND hwnd, UINT, UINT_PTR, DWORD);
//void PaintContent(HWND hwnd, PAINTSTRUCT *pps);
//void In(TCHAR src, char* drc);
//
//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
//	, LPSTR lpszCmdParam, int nCmdShow)
//{
//	AllocConsole();
//	HWND hWnd;
//	MSG Message;
//	WNDCLASS WndClass;
//	g_hInst = hInstance;
//
//
//	WndClass.cbClsExtra = 0;
//	WndClass.cbWndExtra = 0;
//	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	WndClass.hInstance = hInstance;
//	WndClass.lpfnWndProc = (WNDPROC)WndProc;
//	WndClass.lpszClassName = lpszClass;
//	WndClass.lpszMenuName = NULL;
//	WndClass.style = CS_HREDRAW | CS_VREDRAW;
//	RegisterClass(&WndClass);
//
//	hWnd = CreateWindow(lpszClass, TEXT("Detector"), WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
//		NULL, (HMENU)NULL, hInstance, NULL);
//	ShowWindow(hWnd, nCmdShow);
//
//	while (GetMessage(&Message, 0, 0, 0)) {
//		TranslateMessage(&Message);
//		DispatchMessage(&Message);
//	}
//	return Message.wParam;
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
//{
//	HDC hdc;
//	switch (iMessage) {
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		return 0;
//
//	case WM_LBUTTONDOWN:
//		hdc = GetDC(hWnd);
//		ReleaseDC(hWnd, hdc);
//		return 0;
//
//	case WM_CREATE:
//		return OnCreate(hWnd, NULL);
//	}
//
//	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
//}
//
//TCHAR g_szPath[MAX_PATH];
//TCHAR g_szItem[MAX_PATH];
//char path[10][MAX_PATH];
//
//void CALLBACK Detect(HWND hwnd, UINT, UINT_PTR, DWORD)
//{
//	HWND hwndFind = GetForegroundWindow();
//	g_szPath[0] = TEXT('\0');
//	g_szItem[0] = TEXT('\0');
//	int PathCount = 0;
//	IShellWindows *psw;
//	if (SUCCEEDED(CoCreateInstance(CLSID_ShellWindows, NULL, CLSCTX_ALL,
//		IID_IShellWindows, (void**)&psw))) {
//		VARIANT v;
//		V_VT(&v) = VT_I4;
//		IDispatch  *pdisp;
//		BOOL fFound = FALSE;
//		for (V_I4(&v) = 0; !fFound && psw->Item(v, &pdisp) == S_OK;
//			V_I4(&v)++) {
//			IWebBrowserApp *pwba;
//			if (SUCCEEDED(pdisp->QueryInterface(IID_IWebBrowserApp, (void**)&pwba))) {
//				HWND hwndWBA;
//				if (SUCCEEDED(pwba->get_HWND((LONG_PTR*)&hwndWBA)) &&
//					hwndWBA == hwndFind) {
//					fFound = TRUE;
//					IServiceProvider *psp;
//					if (SUCCEEDED(pwba->QueryInterface(IID_IServiceProvider, (void**)&psp))) {
//						IShellBrowser *psb;
//						if (SUCCEEDED(psp->QueryService(SID_STopLevelBrowser,
//							IID_IShellBrowser, (void**)&psb))) {
//							IShellView *psv;
//							if (SUCCEEDED(psb->QueryActiveShellView(&psv))) {
//								IFolderView *pfv;
//								if (SUCCEEDED(psv->QueryInterface(IID_IFolderView,
//									(void**)&pfv))) {
//									IPersistFolder2 *ppf2;
//									if (SUCCEEDED(pfv->GetFolder(IID_IPersistFolder2,
//										(void**)&ppf2))) {
//										LPITEMIDLIST pidlFolder;
//										if (SUCCEEDED(ppf2->GetCurFolder(&pidlFolder))) {
//											if (!SHGetPathFromIDList(pidlFolder, g_szPath)) {
//												lstrcpyn(g_szPath, TEXT("<not a directory>"), MAX_PATH);
//											}
//											int iFocus;
//											if (SUCCEEDED(pfv->GetFocusedItem(&iFocus))) {
//												LPITEMIDLIST pidlItem;
//												if (SUCCEEDED(pfv->Item(iFocus, &pidlItem))) {
//													IShellFolder *psf;
//													if (SUCCEEDED(ppf2->QueryInterface(IID_IShellFolder,
//														(void**)&psf))) {
//														STRRET str;
//														if (SUCCEEDED(psf->GetDisplayNameOf(pidlItem,
//															SHGDN_INFOLDER,
//															&str))) {
//															StrRetToBuf(&str, pidlItem, g_szItem, MAX_PATH);
//														}
//														psf->Release();
//													}
//													CoTaskMemFree(pidlItem);
//												}
//											}
//											CoTaskMemFree(pidlFolder);
//										}
//										ppf2->Release();
//									}
//									pfv->Release();
//								}
//								psv->Release();
//							}
//							psb->Release();
//						}
//						psp->Release();
//					}
//				}
//				pwba->Release();
//			}
//			pdisp->Release();
//		}
//		psw->Release();
//	}
//	InvalidateRect(hwnd, NULL, TRUE);
//}
//
//BOOL
//OnCreate(HWND hwnd, LPCREATESTRUCT lpcs)
//{
//	HDC hdc;
//	PAINTSTRUCT ps;
//	hdc = GetDC(hwnd);
//	ps.hdc = hdc;
//	PaintContent(hwnd, &ps);
//	cout << path[0], path[1];
//	ReleaseDC(hwnd, hdc);
//	SetTimer(hwnd, 1, 1000, (TIMERPROC)Detect);
//	return TRUE;
//}
//
//void
//PaintContent(HWND hwnd, PAINTSTRUCT *pps)
//{
//	TextOut(pps->hdc, 0, 0, g_szPath, lstrlen(g_szPath));
//	TextOut(pps->hdc, 0, 20, g_szItem, lstrlen(g_szItem));
//}