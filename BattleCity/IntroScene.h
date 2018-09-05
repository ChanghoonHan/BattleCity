#pragma once
#include "Scene.h"

class IntroScene :
	public Scene
{
	float m_fIntroMapPosY;
	float m_fStackElapsedTime;
	bool m_bIsFirstTanckBMP;
	bool m_bIsEndScene;

public:
	virtual void FirstInitScene(HDC& hdc);
	virtual void InitScene();
	virtual void OperatorInput(MYKEYVAL key);
	virtual void Update(float fElapsedTime);
	virtual SCENENUM Draw(HDC& hdc);

	IntroScene();
	virtual ~IntroScene();
};

