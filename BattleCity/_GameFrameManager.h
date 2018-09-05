#pragma once
#include <Windows.h>

class GameFrameManager
{
	HWND m_hWnd;
	DWORD m_dwCurTime;
	DWORD m_dwOldTime;
	float m_fElapsedTime;

	void Update();
	void Draw();
	void OperatorInput();

public:
	void Init(HWND& hWnd);
	void PlayFrame();
	void Release();
	
	GameFrameManager();
	~GameFrameManager();
};

