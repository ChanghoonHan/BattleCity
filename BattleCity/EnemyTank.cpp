#include "EnemyTank.h"
#include <random>

void EnemyTank::Init()
{
	Tank::Init();
	m_fOldTankPosX = (int)m_fTankPosX;
	m_fOldTankPosY = (int)m_fTankPosY;
	
	int randNum = rand() % 10;
	if (randNum < 2)
	{
		m_bIsPowerUp = true;
		m_fMaxReLoadTime = 0.8;
		m_iTankSpeed = TANKSPEED * 1.5;
	}
	else
	{
		m_bIsPowerUp = false;
		m_fMaxReLoadTime = 1.5;
		m_iTankSpeed = TANKSPEED;
	}

	m_fStackTimeForChangeDirect = 0;
	m_fStackTimeForChangeDirect2 = 0;
	m_key = MYKEYVAL_DOWN;
}

void EnemyTank::SetCollider()
{
	if (m_curDirect == DIRECT_UP)
	{
		SetRect(&m_collider, m_fTankPosX, m_fTankPosY, m_fTankPosX + 40, m_fTankPosY + 35);
		return;
	}

	if (m_curDirect == DIRECT_DOWN)
	{
		SetRect(&m_collider, m_fTankPosX, m_fTankPosY + 5, m_fTankPosX + 40, m_fTankPosY + 40);
		return;
	}

	if (m_curDirect == DIRECT_LEFT)
	{
		SetRect(&m_collider, m_fTankPosX, m_fTankPosY, m_fTankPosX + 35, m_fTankPosY + 40);
		return;
	}

	if (m_curDirect == DIRECT_RIGHT)
	{
		SetRect(&m_collider, m_fTankPosX + 5, m_fTankPosY, m_fTankPosX + 40, m_fTankPosY + 40);
	}
}

void EnemyTank::Update(float fElapsedTime)
{
	m_fStackTimeForChangeDirect2 += fElapsedTime;

	if (m_fOldTankPosX == (int)m_fTankPosX && m_fOldTankPosY == (int)m_fTankPosY)
	{
		m_fStackTimeForChangeDirect += fElapsedTime;
	}
	else
	{
		m_fStackTimeForChangeDirect = 0;
	}

	if (m_fStackTimeForChangeDirect > 0.2 || m_fStackTimeForChangeDirect2 > 2)
	{
		m_fStackTimeForChangeDirect2 = 0;
		m_fStackTimeForChangeDirect = 0;
		m_key = (MYKEYVAL)(rand() % 5);
		if (m_key == 4)
		{
			m_key = MYKEYVAL_DOWN;
		}
	}

	if (m_fOldTankPosX != (int)m_fTankPosX)
	{
		m_fOldTankPosX = (int)m_fTankPosX;
	}

	if (m_fOldTankPosY != (int)m_fTankPosY)
	{
		m_fOldTankPosY = (int)m_fTankPosY;
	}

	OperatorInput(m_key);
	Tank::Update(fElapsedTime);

	if (m_fLiveTime > 1 && m_bIsLive && !m_bIsExplode)
	{
		FireMissile();
	}
	
}

void EnemyTank::Draw(HDC hdc)
{
	Tank::Draw(hdc);

	if (!m_bIsLive || m_bIsExplode)
	{
		return;
	}

	switch (m_curDirect)
	{
	case DIRECT_UP:
		if (m_bIsFirstTankBitMap)
		{
			m_lpBitMapManager->Draw(hdc, UNIT_ENEMYUP1, m_fTankPosX, m_fTankPosY, 40, 40);
		}
		else
		{
			if (m_bIsPowerUp)
			{
				m_lpBitMapManager->Draw(hdc, UNIT_ENEMYUP3, m_fTankPosX, m_fTankPosY, 40, 40);
			}
			else
			{
				m_lpBitMapManager->Draw(hdc, UNIT_ENEMYUP2, m_fTankPosX, m_fTankPosY, 40, 40);
			}
		}

		break;

	case DIRECT_RIGHT:
		if (m_bIsFirstTankBitMap)
		{
			m_lpBitMapManager->Draw(hdc, UNIT_ENEMYRIGHT1, m_fTankPosX, m_fTankPosY, 40, 40);
		}
		else
		{
			if (m_bIsPowerUp)
			{
				m_lpBitMapManager->Draw(hdc, UNIT_ENEMYRIGHT3, m_fTankPosX, m_fTankPosY, 40, 40);
			}
			else
			{
				m_lpBitMapManager->Draw(hdc, UNIT_ENEMYRIGHT2, m_fTankPosX, m_fTankPosY, 40, 40);
			}
		}
		break;

	case DIRECT_DOWN:
		if (m_bIsFirstTankBitMap)
		{
			m_lpBitMapManager->Draw(hdc, UNIT_ENEMYDOWN1, m_fTankPosX, m_fTankPosY, 40, 40);
		}
		else
		{
			if (m_bIsPowerUp)
			{
				m_lpBitMapManager->Draw(hdc, UNIT_ENEMYDOWN3, m_fTankPosX, m_fTankPosY, 40, 40);
			}
			else
			{
				m_lpBitMapManager->Draw(hdc, UNIT_ENEMYDOWN2, m_fTankPosX, m_fTankPosY, 40, 40);
			}
		}

		break;

	case DIRECT_LEFT:
		if (m_bIsFirstTankBitMap)
		{
			m_lpBitMapManager->Draw(hdc, UNIT_ENEMYLEFT1, m_fTankPosX, m_fTankPosY, 40, 40);
		}
		else
		{
			if (m_bIsPowerUp)
			{
				m_lpBitMapManager->Draw(hdc, UNIT_ENEMYLEFT3, m_fTankPosX, m_fTankPosY, 40, 40);
			}
			else
			{
				m_lpBitMapManager->Draw(hdc, UNIT_ENEMYLEFT2, m_fTankPosX, m_fTankPosY, 40, 40);
			}
		}
		break;
	default:
		break;
	}
}

EnemyTank::EnemyTank()
{
}


EnemyTank::~EnemyTank()
{
}
