#pragma once
#include "Scene.h"
class SetStageScene :
	public Scene
{
	float m_fBack1PosY;
	float m_fBack2PosY;
	float m_fStackElapseTimeForKey;
	bool m_bIsKeyIn;
	bool m_bIsSelectStage;

public:
	virtual void FirstInitScene(HDC& hdc);
	virtual void InitScene();
	virtual void OperatorInput(MYKEYVAL key);
	virtual void Update(float fElapsedTime);
	virtual SCENENUM Draw(HDC& hdc);

	SetStageScene();
	virtual ~SetStageScene();
};

