#include "GameClearScene.h"

void GameClearScene::InitScene()
{
	if (m_iKilledEnemyCount == 20)
	{
		m_bIsGameOver = false;
	}
	else
	{
		m_bIsGameOver = true;
	}
	m_iEnemyCount = 0;
	m_fElapsedTime = 0;
}

void GameClearScene::Update(float fElapsedTime)
{
	m_fElapsedTime += fElapsedTime;
	if (m_fElapsedTime > 0.2 && m_iKilledEnemyCount != 0)
	{
		m_fElapsedTime = 0;
		m_iKilledEnemyCount--;
		m_iEnemyCount++;
		m_iScore += 100;
	}
}

SCENENUM GameClearScene::Draw(HDC& hdc)
{
	char buf[20];
	m_lpbitMapManager->Draw(hdc, BACK_BLACKBASE, 0, 0, 800, 700);
	m_lpbitMapManager->Draw(hdc, UNIT_ENEMYUP1, 430, 300, 40, 40);

	SetTextColor(hdc, RGB(255, 0, 0));
	TextOut(hdc, 150, 50, "HIGH SCORE", strlen("HIGH SCORE"));
	TextOut(hdc, 80, 150, "1 - PLAYER", strlen("1 - PLAYER"));
	SetTextColor(hdc, RGB(251, 159, 0));
	sprintf(buf, "%d", m_iHighScore);
	TextOut(hdc, 460, 50, buf, strlen(buf));
	sprintf(buf, "%d", m_iScore);
	RECT rect = { 80, 200, 310, 250 };
	DrawText(hdc, buf, strlen(buf), &rect, DT_RIGHT);

	SetTextColor(hdc, RGB(255, 255, 255));
	sprintf(buf, "%d¡ç", m_iEnemyCount);
	rect = { 250, 295, 425, 350 };
	DrawText(hdc, buf, strlen(buf), &rect, DT_RIGHT);
	

	sprintf(buf, "PTS");
	rect = { 150, 295, 310, 350 };
	DrawText(hdc, buf, strlen(buf), &rect, DT_RIGHT);

	sprintf(buf, "TOTAL");
	rect = { 150, 500, 310, 550 };
	DrawText(hdc, buf, strlen(buf), &rect, DT_RIGHT);

	if (m_fElapsedTime > 0.4)
	{
		sprintf(buf, "%d", m_iEnemyCount);
		rect = { 250, 500, 405, 550 };
		DrawText(hdc, buf, strlen(buf), &rect, DT_RIGHT);
	}

	sprintf(buf, "%d", m_iEnemyCount * 100);
	rect = { 100, 295, 220, 350 };
	DrawText(hdc, buf, strlen(buf), &rect, DT_RIGHT);

	sprintf(buf, "STAGE  %d", m_iStage);
	TextOut(hdc, 300, 100, buf, strlen(buf));

	if (m_fElapsedTime > 3)
	{
		if (m_bIsGameOver)
		{
			m_iScore = 0;
			return SCENENUM_GAMEOVER;
		}
		else
		{
			if (m_iStage == 3)
			{
				m_iScore = 0;
				return SCENENUM_INTRO;
			}
			m_iStage++;
			return SCENENUM_GAME;
		}
	}

	return SCENENUM_GAMECLEAR;
}

GameClearScene::GameClearScene()
{
}


GameClearScene::~GameClearScene()
{
}
