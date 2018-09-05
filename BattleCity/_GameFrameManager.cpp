#include "_GameFrameManager.h"
#include "SceneManager.h"
#include <random>

void GameFrameManager::OperatorInput()
{
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		SceneManager::GetInstance()->OperatorInput(MYKEYVAL_SPACE);
	}

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		SceneManager::GetInstance()->OperatorInput(MYKEYVAL_LEFT);
	}

	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		SceneManager::GetInstance()->OperatorInput(MYKEYVAL_RIGHT);
	}

	if (GetKeyState(VK_UP) & 0x8000)
	{
		SceneManager::GetInstance()->OperatorInput(MYKEYVAL_UP);
	}

	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		SceneManager::GetInstance()->OperatorInput(MYKEYVAL_DOWN);
	}
}

void GameFrameManager::Update()
{
	SceneManager::GetInstance()->Update(m_fElapsedTime);
}

void GameFrameManager::Draw()
{
	HDC hdc = GetDC(m_hWnd);
	SceneManager::GetInstance()->Draw(hdc);
	ReleaseDC(m_hWnd, hdc);
}
/////////////////////////////////////////////////////////////////////////////////////////////
void GameFrameManager::Init(HWND& hWnd)
{
	srand(GetTickCount());
	HDC hdc = GetDC(m_hWnd);
	m_hWnd = hWnd;
	m_dwOldTime = GetTickCount();
	m_dwCurTime = GetTickCount();
	SceneManager::GetInstance()->InitSceneManager(hdc);
	ReleaseDC(m_hWnd, hdc);
}

void GameFrameManager::PlayFrame()
{
	m_dwCurTime = GetTickCount();
	m_fElapsedTime = (m_dwCurTime - m_dwOldTime) / 1000.0f;
	m_dwOldTime = m_dwCurTime;

	OperatorInput();
	Update();
	Draw();
}

void GameFrameManager::Release()
{
	SceneManager::GetInstance()->ReleaseSceneManagerVal();
	SceneManager::GetInstance()->ReleaseSceneManager();
}

GameFrameManager::GameFrameManager()
{
}


GameFrameManager::~GameFrameManager()
{
}
