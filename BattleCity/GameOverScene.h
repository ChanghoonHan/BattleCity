#pragma once
#include "Scene.h"
class GameOverScene :
	public Scene
{
	float m_fBitMapPos;
	float m_fGameSceneEndWaitTime;

public:
	virtual void FirstInitScene(HDC& hdc) {};
	virtual void InitScene();
	virtual void OperatorInput(MYKEYVAL key) {};
	virtual void Update(float fElapsedTime);
	virtual SCENENUM Draw(HDC& hdc);

	GameOverScene();
	virtual ~GameOverScene();
};

