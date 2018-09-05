#include "GameOverScene.h"

void GameOverScene::InitScene()
{
	m_fBitMapPos = WINDOWHEIGHT;
	m_fGameSceneEndWaitTime = 0;
}

void GameOverScene::Update(float fElapsedTime)
{
	m_fBitMapPos -= 300 * fElapsedTime;
	if (m_fBitMapPos < 0)
	{
		m_fBitMapPos = 0;
		m_fGameSceneEndWaitTime += fElapsedTime;
	}
}

SCENENUM GameOverScene::Draw(HDC& hdc)
{
	m_lpbitMapManager->Draw(hdc, BACK_BLACKBASE, 0, 0, 800, 700);
	m_lpbitMapManager->Draw(hdc, BACK_GAMEOVER, 0, m_fBitMapPos, 800, 700);

	if (m_fBitMapPos == 0)
	{
		if (m_fGameSceneEndWaitTime > 2)
		{
			m_iScore = 0;
			m_iStage = 0;
			m_iKilledEnemyCount = 0;
			return SCENENUM_INTRO;
		}
	}

	return SCENENUM_GAMEOVER;
}

GameOverScene::GameOverScene()
{
}


GameOverScene::~GameOverScene()
{
}
