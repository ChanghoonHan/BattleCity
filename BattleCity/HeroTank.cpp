#include "HeroTank.h"

void HeroTank::Init()
{
	Tank::Init();
	m_fMaxReLoadTime = 0.5;
	m_iTankSpeed = TANKSPEED * 2;
	m_bIsHero = true;
	m_fShieldBitMapChangeTime = 0;
	m_bOnShield = true;
	m_bIsFirstShieldBitMap = true;
}

void HeroTank::Update(float fElapsedTime)
{
	Tank::Update(fElapsedTime);

	if (m_bOnShield)
	{
		m_fShieldBitMapChangeTime += fElapsedTime;
		if (m_fShieldBitMapChangeTime > 0.2)
		{
			m_fShieldBitMapChangeTime = 0;
			m_bIsFirstShieldBitMap = !m_bIsFirstShieldBitMap;
		}
	}

	if (m_fLiveTime > 15)
	{
		m_bOnShield = false;
	}
}

void HeroTank::Draw(HDC hdc)
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
			m_lpBitMapManager->Draw(hdc, UNIT_HEROUP1, m_fTankPosX, m_fTankPosY, 40, 40);
		}
		else
		{
			m_lpBitMapManager->Draw(hdc, UNIT_HEROUP2, m_fTankPosX, m_fTankPosY, 40, 40);
		}
		
		break;

	case DIRECT_RIGHT:
		if (m_bIsFirstTankBitMap)
		{
			m_lpBitMapManager->Draw(hdc, UNIT_HERORIGHT1, m_fTankPosX, m_fTankPosY, 40, 40);
		}
		else
		{
			m_lpBitMapManager->Draw(hdc, UNIT_HERORIGHT2, m_fTankPosX, m_fTankPosY, 40, 40);
		}
		break;

	case DIRECT_DOWN:
		if (m_bIsFirstTankBitMap)
		{
			m_lpBitMapManager->Draw(hdc, UNIT_HERODOWN1, m_fTankPosX, m_fTankPosY, 40, 40);
		}
		else
		{
			m_lpBitMapManager->Draw(hdc, UNIT_HERODOWN2, m_fTankPosX, m_fTankPosY, 40, 40);
		}

		break;
	case DIRECT_LEFT:
		if (m_bIsFirstTankBitMap)
		{
			m_lpBitMapManager->Draw(hdc, UNIT_HEROLEFT1, m_fTankPosX, m_fTankPosY, 40, 40);
		}
		else
		{
			m_lpBitMapManager->Draw(hdc, UNIT_HEROLEFT2, m_fTankPosX, m_fTankPosY, 40, 40);
		}
		break;
	default:
		break;
	}
	
	if (m_bOnShield)
	{
		if (m_bIsFirstShieldBitMap)
		{
			m_lpBitMapManager->Draw(hdc, EFFECT_SHIELD1, m_fTankPosX, m_fTankPosY, 40, 40);
		}
		else
		{
			m_lpBitMapManager->Draw(hdc, EFFECT_SHIELD2, m_fTankPosX, m_fTankPosY, 40, 40);
		}
	}
}

void HeroTank::SetCollider()
{
	if (m_curDirect == DIRECT_UP)
	{
		SetRect(&m_collider, m_fTankPosX, m_fTankPosY, m_fTankPosX + 40, m_fTankPosY + 30);
		return;
	}

	if (m_curDirect == DIRECT_DOWN)
	{
		SetRect(&m_collider, m_fTankPosX, m_fTankPosY + 10, m_fTankPosX + 40, m_fTankPosY + 40);
		return;
	}

	if (m_curDirect == DIRECT_LEFT)
	{
		SetRect(&m_collider, m_fTankPosX, m_fTankPosY, m_fTankPosX + 30, m_fTankPosY + 40);
		return;
	}

	if (m_curDirect == DIRECT_RIGHT)
	{
		SetRect(&m_collider, m_fTankPosX + 10, m_fTankPosY, m_fTankPosX + 40, m_fTankPosY + 40);
	}
}

void HeroTank::CheckCollisionWithMissile()
{
	if (m_bOnShield)
	{
		return;
	}

	Tank::CheckCollisionWithMissile();
}

HeroTank::HeroTank()
{
}


HeroTank::~HeroTank()
{
}
