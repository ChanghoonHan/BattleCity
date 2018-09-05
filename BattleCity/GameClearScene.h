#pragma once
#include "Scene.h"
class GameClearScene :
	public Scene
{
	int m_iEnemyCount;
	float m_fElapsedTime;
	bool m_bIsGameOver;

public:
	virtual void FirstInitScene(HDC& hdc) {};
	virtual void InitScene();
	virtual void OperatorInput(MYKEYVAL key) {};
	virtual void Update(float fElapsedTime);
	virtual SCENENUM Draw(HDC& hdc);

	GameClearScene();
	virtual ~GameClearScene();
};

