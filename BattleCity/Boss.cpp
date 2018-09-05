#include "Boss.h"

bool Boss::CheckCollWithMissile(vector<MissileCollider> missileColliderList)
{
	RECT rect;
	for (auto iter = missileColliderList.begin(); iter != missileColliderList.end(); iter++)
	{
		if (IntersectRect(&rect, &m_collider, &(iter->m_collider)))
		{
			return true;
		}
	}
	
	return false;
}

void Boss::Init(BitMapManager* lpBitMapManager)
{
	m_lpBitMapManager = lpBitMapManager;
	m_fElapsedTime = 0;
	m_bIsLive = true;
	m_bIsExplode = false;
	m_collider = { 350, 625, 400, 775 };
}

void Boss::Update(vector<MissileCollider> missileColliderList, float fElapsedTime)
{
	if (m_bIsExplode)
	{
		m_fElapsedTime += fElapsedTime;
		if (m_fElapsedTime >0.4)
		{
			m_bIsLive = false;
		}
		return;
	}

	if (CheckCollWithMissile(missileColliderList))
	{
		m_bIsExplode = true;
	}
}

void Boss::Draw(HDC& hdc)
{
	if (!m_bIsExplode)
	{
		m_lpBitMapManager->Draw(hdc, UNIT_BOSS, 350, 625, 50, 50);
	}
	else
	{
		if (m_fElapsedTime < 0.15)
		{
			m_lpBitMapManager->Draw(hdc, EFFECT_EXPLOSION4, 345, 620, 60, 60);
		}
		else if (m_fElapsedTime < 0.3)
		{
			m_lpBitMapManager->Draw(hdc, EFFECT_EXPLOSION5, 335, 610, 80, 80);
		}
		else
		{
			m_lpBitMapManager->Draw(hdc, UNIT_BOSSDIE, 350, 625, 50, 50);
		}
	}
}

RECT Boss::GetCollider()
{
	if (m_bIsLive)
	{
		return m_collider;
	}
	
	return	{ 0,0,0,0 };
}

bool Boss::IsBossDie()
{
	return !m_bIsLive;
}

Boss::Boss()
{
}


Boss::~Boss()
{
}
