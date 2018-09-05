#pragma once
#include <Windows.h>
#include "BitMapManager.h"

#define WINDOWWIDTH 800
#define WINDOWHEIGHT 700

class BitMapManager;

enum MYKEYVAL
{
	MYKEYVAL_UP,
	MYKEYVAL_DOWN,
	MYKEYVAL_LEFT,
	MYKEYVAL_RIGHT,
	MYKEYVAL_SPACE,
	MYKEYVAL_NULL,
};

enum SCENENUM
{
	SCENENUM_INTRO,
	SCENENUM_SETSTAGE,
	SCENENUM_GAME,
	SCENENUM_GAMECLEAR,
	SCENENUM_GAMEOVER,
	SCENENUM_END,
};

class Scene
{
protected:
	static BitMapManager* m_lpbitMapManager;
	static int m_iHighScore;
	static int m_iStage;
	static int m_iKilledEnemyCount;
	static int m_iScore;

public:
	static void SetBitMapManager(BitMapManager* m_BitMapManager);
	virtual void FirstInitScene(HDC& hdc) = 0;
	virtual void InitScene() = 0;
	virtual void OperatorInput(MYKEYVAL key) = 0;
	virtual void Update(float fElapsedTime) = 0;
	virtual SCENENUM Draw(HDC& hdc) = 0;

	Scene();
	virtual ~Scene();
};