#include "IntroScene.h"

void IntroScene::FirstInitScene(HDC& hdc)
{
	m_fIntroMapPosY = WINDOWHEIGHT;
	m_bIsFirstTanckBMP = true;
	m_bIsEndScene = false;
	m_fStackElapsedTime = 0;
}

void IntroScene::InitScene()
{
	m_fIntroMapPosY = WINDOWHEIGHT;
	m_bIsFirstTanckBMP = true;
	m_bIsEndScene = false;
	m_fStackElapsedTime = 0;
}

void IntroScene::OperatorInput(MYKEYVAL key)
{
	if (m_fIntroMapPosY != 0)
	{
		return;
	}

	if (key != MYKEYVAL_SPACE)
	{
		return;
	}

	m_bIsEndScene = true;
}

void IntroScene::Update(float fElapsedTime)
{
	m_fStackElapsedTime += fElapsedTime;

	if (m_fStackElapsedTime > 0.1)
	{
		m_bIsFirstTanckBMP = !m_bIsFirstTanckBMP;
		m_fStackElapsedTime = 0;
	}

	m_fIntroMapPosY = m_fIntroMapPosY - (200 * fElapsedTime);
	if (m_fIntroMapPosY < 0)
	{
		m_fIntroMapPosY = 0;
	}
}

SCENENUM IntroScene::Draw(HDC& hdc)
{
	m_lpbitMapManager->Draw(hdc, BACK_BLACKBASE, 0, 0, WINDOWWIDTH, WINDOWHEIGHT);
	m_lpbitMapManager->Draw(hdc, BACK_INTRO, 0, m_fIntroMapPosY, WINDOWWIDTH, WINDOWHEIGHT);

	if (m_fIntroMapPosY == 0)
	{
		if (m_bIsFirstTanckBMP)
		{
			m_lpbitMapManager->Draw(hdc, UNIT_HERORIGHT1, 230, 387, 50, 50);
		}
		else
		{
			m_lpbitMapManager->Draw(hdc, UNIT_HERORIGHT2, 230, 387, 50, 50);
		}
	}

	if (m_bIsEndScene)
	{
		return SCENENUM_SETSTAGE;
	}

	return SCENENUM_INTRO;
}

IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{
}
