#include <Windows.h>
#include <crtdbg.h>
#include "_GameFrameManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
char lpszClass[256] = "First";
GameFrameManager gameFrameManager;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace,
	LPSTR lpszCmdParam, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();
	//_CrtSetBreakAlloc(202);

	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;//통산 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//미리만들어놓은 브러쉬 가져옴
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;//프로시저 받아옴 메세지 재정의를 모아놓은 함수
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//윈도우 스타일

	RegisterClass(&WndClass);//os에 윈도우 등록

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		0, 0, (800 + 16), (700 + 39),
		NULL, (HMENU)NULL, hInstance, NULL);
	//CW_ ->x y wid hei
	//부모윈도우, idset, instand, NULL

	ShowWindow(hWnd, nCmdShow);//한번 그려옴
	
	gameFrameManager.Init(hWnd);

	while (true)
	{
		/// 메시지큐에 메시지가 있으면 메시지 처리
		if (PeekMessage(&Message, NULL, 0U, 0U, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
				break;

			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		//else
		//{
		gameFrameManager.PlayFrame();
		//}
	}

	gameFrameManager.Release();

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
//핸들, 어떤메세지, 부가정보1, 부가정보2
{
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//큐에 나간다는메세지 적재
		return 0;

	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));//기본 메세지처리..
}