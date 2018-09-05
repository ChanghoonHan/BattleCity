#pragma once
#include "Scene.h"
#include "BitMapManager.h"
#include "IntroScene.h"
#include "SetStageScene.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "GameClearScene.h"

class SceneManager
{
	HDC m_memDC;
	HBITMAP m_newBitMap;
	HBITMAP m_oldBitMap;

	HFONT m_hOldFont;
	HFONT m_hNewFont;

	bool m_isSceneChage;

	int m_sceneNum;
	BitMapManager m_bitMapManager;
	Scene* m_scenes[SCENENUM_END];

	static SceneManager* S;
	SceneManager();

public:
	void InitScene();
	void OperatorInput(MYKEYVAL key);
	void Draw(HDC& hdc);
	void Update(float fElapsedTime);

	void InitSceneManager(HDC& hdc);
	void ReleaseSceneManagerVal();

	static SceneManager* GetInstance();
	static void ReleaseSceneManager();
	~SceneManager();
};