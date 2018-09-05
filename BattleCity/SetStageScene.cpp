#include "SetStageScene.h"

void SetStageScene::FirstInitScene(HDC& hdc)
{
	m_fBack1PosY = 0 - WINDOWHEIGHT / 2;
	m_fBack2PosY = WINDOWHEIGHT;
	m_iStage = 1;
	m_bIsSelectStage = false;
	m_fStackElapseTimeForKey = 0;
	m_bIsKeyIn = false;
}

void SetStageScene::InitScene()
{
	m_fBack1PosY = 0 - WINDOWHEIGHT / 2;
	m_fBack2PosY = WINDOWHEIGHT;	
	m_iStage = 1;
	m_bIsSelectStage = false;
	m_fStackElapseTimeForKey = 0;
	m_bIsKeyIn = false;
}

void SetStageScene::OperatorInput(MYKEYVAL key)
{
	if (m_fBack1PosY != 0 || m_bIsKeyIn)
	{
		return;
	}

	m_bIsKeyIn = true;

	switch (key)
	{
	case MYKEYVAL_UP:
		m_iStage++;
		if (m_iStage > 3)
		{
			m_iStage = 3;
		}
		break;
	case MYKEYVAL_DOWN:
		m_iStage--;
		if (m_iStage < 1)
		{
			m_iStage = 1;
		}
		break;
	case MYKEYVAL_SPACE:
		m_bIsSelectStage = true;
		break;
	default:
		break;
	}
}

void SetStageScene::Update(float fElapsedTime)
{
	if (m_bIsKeyIn)
	{
		m_fStackElapseTimeForKey += fElapsedTime;
		if (m_fStackElapseTimeForKey > 0.5)
		{
			m_fStackElapseTimeForKey = 0;
			m_bIsKeyIn = false;
		}
	}

	m_fBack1PosY = m_fBack1PosY + (300 * fElapsedTime);
	if (m_fBack1PosY > 0)
	{
		m_fBack1PosY = 0;
	}

	m_fBack2PosY = m_fBack2PosY - (300 * fElapsedTime);
	if (m_fBack2PosY < WINDOWHEIGHT / 2)
	{
		m_fBack2PosY = WINDOWHEIGHT / 2;
	}
}

SCENENUM SetStageScene::Draw(HDC& hdc)
{
	char stageStr[32] = "";
	sprintf(stageStr, "STAGE  %d", m_iStage);

	m_lpbitMapManager->Draw(hdc, BACK_SETSTAGE, 0, m_fBack1PosY, WINDOWWIDTH, WINDOWHEIGHT / 2);
	m_lpbitMapManager->Draw(hdc, BACK_SETSTAGE, 0, m_fBack2PosY, WINDOWWIDTH, WINDOWHEIGHT / 2);

	if (m_fBack1PosY == 0)
	{
		TextOut(hdc, WINDOWWIDTH / 2 - 100, WINDOWHEIGHT / 2 - 25, stageStr, strlen(stageStr));
	}

	if (m_bIsSelectStage)
	{
		return SCENENUM_GAME;
	}

	return SCENENUM_SETSTAGE;
}

SetStageScene::SetStageScene()
{
}


SetStageScene::~SetStageScene()
{
}
