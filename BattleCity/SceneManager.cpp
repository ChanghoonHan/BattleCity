#include "SceneManager.h"

#define SAFE_DELETE(a) if((a) != NULL) delete (a); (a)= NULL;

SceneManager* SceneManager::S = NULL;

void SceneManager::OperatorInput(MYKEYVAL key)
{
	m_scenes[m_sceneNum]->OperatorInput(key);
}


void SceneManager::Update(float fElapsedTime)
{
	if (m_isSceneChage)
	{
		m_isSceneChage = false;
		m_scenes[m_sceneNum]->InitScene();
	}
	m_scenes[m_sceneNum]->Update(fElapsedTime);
}

void SceneManager::Draw(HDC& hdc)
{
	int sceneNum = m_scenes[m_sceneNum]->Draw(m_memDC);
	TransparentBlt(hdc, 0, 0, WINDOWWIDTH, WINDOWHEIGHT, m_memDC, 0, 0, WINDOWWIDTH, WINDOWHEIGHT, RGB(255, 0, 255));

	if (sceneNum != m_sceneNum)
	{
		m_isSceneChage = true;
		m_sceneNum = sceneNum;
	}
}

void SceneManager::InitScene()
{
	if (m_isSceneChage)
	{
		m_isSceneChage = false;
		m_scenes[m_sceneNum]->InitScene();
	}
}

void SceneManager::InitSceneManager(HDC& hdc)
{
	m_memDC = CreateCompatibleDC(hdc);
	m_newBitMap = CreateCompatibleBitmap(hdc, WINDOWWIDTH, WINDOWHEIGHT);
	m_oldBitMap = (HBITMAP)SelectObject(m_memDC, m_newBitMap);
	SetBkMode(m_memDC, TRANSPARENT);//글자 배경투명 시작

	m_hNewFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, "consolas");
	m_hOldFont = (HFONT)SelectObject(m_memDC, m_hNewFont);

	m_isSceneChage = true;
	m_sceneNum = 0;
	m_bitMapManager.InitBitMapManager(m_memDC);

	Scene::SetBitMapManager(&m_bitMapManager);
	//////////////////////scene추가
	m_scenes[SCENENUM_INTRO] = new IntroScene;
	m_scenes[SCENENUM_INTRO]->FirstInitScene(hdc);
	m_scenes[SCENENUM_SETSTAGE] = new SetStageScene;
	m_scenes[SCENENUM_SETSTAGE]->FirstInitScene(hdc);
	m_scenes[SCENENUM_GAME] = new GameScene();////gameScene
	m_scenes[SCENENUM_GAME]->FirstInitScene(hdc);
	m_scenes[SCENENUM_GAMECLEAR] = new GameClearScene();
	m_scenes[SCENENUM_GAMECLEAR]->FirstInitScene(hdc);
	m_scenes[SCENENUM_GAMEOVER] = new GameOverScene();
	m_scenes[SCENENUM_GAMEOVER]->FirstInitScene(hdc);
}

void SceneManager::ReleaseSceneManagerVal()
{
	SetBkMode(m_memDC, OPAQUE);//글자배경 투명 해제
	SelectObject(m_memDC, m_oldBitMap);
	SelectObject(m_memDC, m_hOldFont);
	DeleteObject(m_hOldFont);
	DeleteDC(m_memDC);
	DeleteObject(m_newBitMap);
	m_bitMapManager.Release();

	for (size_t i = 0; i < SCENENUM_END; i++)
	{
		SAFE_DELETE(m_scenes[i]);
	}
}

SceneManager* SceneManager::GetInstance()
{
	if (S == NULL)
	{
		S = new SceneManager;
	}

	return S;
}

void SceneManager::ReleaseSceneManager()
{
	SAFE_DELETE(S);
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}
