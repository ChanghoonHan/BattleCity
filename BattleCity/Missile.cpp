#include "Missile.h"
#include "GameScene.h"

BitMapManager* Missile::m_lpBitMapManager = NULL;
GameScene* Missile::m_lpGameScene = NULL;

void Missile::SetBitMapManager(BitMapManager* lpBitMapManager, GameScene* lpGameScene)
{
	m_lpBitMapManager = lpBitMapManager;
	m_lpGameScene = lpGameScene;
}

void Missile::init()
{
	m_collider = { 0,0,0,0 };
	m_fPosX = 0;
	m_fPosY = 0;
	m_fCenterPosX = 0;
	m_fCenterPosY = 0;
	m_fAfterExplodeTime = 0;
	m_bIsLive = false;
	m_bIsExplode = false;
}

bool Missile::fire(float fPosX, float fPosY, MISSILEDIRECT direct, bool isHeroMissile)
{
	if (m_bIsLive)
	{
		return false;
	}

	m_bIsHeroMissile = isHeroMissile;
	m_fPosX = fPosX;
	m_fPosY = fPosY;
	m_fCenterPosX = 0;
	m_fCenterPosY = 0;
	m_fAfterExplodeTime = 0;
	m_direct = direct;
	m_bIsLive = true;
	m_bIsExplode = false;

	return true;
}

void Missile::Update(float fElapseTime)
{
	if (!m_bIsLive)
	{
		return;
	}

	if (m_bIsExplode)
	{
		m_fAfterExplodeTime += fElapseTime;

		return;
	}

	switch (m_direct)
	{
	case MISSILEDIRECT_UP:
		m_fPosY = m_fPosY - (MISSILESPEED * fElapseTime);
		break;
	case MISSILEDIRECT_RIGHT:
		m_fPosX = m_fPosX + (MISSILESPEED * fElapseTime);
		break;
	case MISSILEDIRECT_LEFT:
		m_fPosX = m_fPosX - (MISSILESPEED * fElapseTime);
		break;
	case MISSILEDIRECT_DOWN:
		m_fPosY = m_fPosY + (MISSILESPEED * fElapseTime);	
		break;
	default:
		break;
	}

	SetCollider();
}
void Missile::CheckCollWithObj()
{
	if (!IsInMap() ||
		m_lpGameScene->CheckCollWithBlock(GetCollider()) ||
		m_lpGameScene->CheckCollWithMissile(GetCollider()) ||
		m_lpGameScene->CheckCollWithTank(GetCollider()))
	{
		m_bIsExplode = true;
	}
}

void Missile::Draw(HDC& hdc)
{
	if (!m_bIsLive)
	{
		return;
	}

	if (m_bIsExplode)
	{
		if (m_fAfterExplodeTime < 0.1)
		{
			m_lpBitMapManager->Draw(hdc, EFFECT_EXPLOSION1, m_fCenterPosX - 20, m_fCenterPosY - 20, 40, 40);
		}
		else if(m_fAfterExplodeTime < 0.2)
		{
			m_lpBitMapManager->Draw(hdc, EFFECT_EXPLOSION2, m_fCenterPosX - 20, m_fCenterPosY - 20, 40, 40);
		}
		else if (m_fAfterExplodeTime < 0.3)
		{
			m_lpBitMapManager->Draw(hdc, EFFECT_EXPLOSION3, m_fCenterPosX - 20, m_fCenterPosY - 20, 40, 40);
		}

		else
		{
			m_bIsLive = false;
		}

		return;
	}


	switch (m_direct)
	{
	case MISSILEDIRECT_UP:
		m_lpBitMapManager->Draw(hdc, UNIT_MISSILEUP, m_fPosX, m_fPosY, 10, 16);
		break;
	case MISSILEDIRECT_RIGHT:
		m_lpBitMapManager->Draw(hdc, UNIT_MISSILERIGHT, m_fPosX, m_fPosY, 16, 10);
		break;
	case MISSILEDIRECT_LEFT:
		m_lpBitMapManager->Draw(hdc, UNIT_MISSILELEFT, m_fPosX, m_fPosY, 16, 10);
		break;
	case MISSILEDIRECT_DOWN:
		m_lpBitMapManager->Draw(hdc, UNIT_MISSILEDOWN, m_fPosX, m_fPosY, 10, 16);
		break;
	default:
		break;
	}
}

void Missile::SetCollider()
{
	if (!m_bIsLive || m_bIsExplode)
	{
		SetRect(&m_collider, 0,0,0,0);
		m_fCenterPosX = (m_collider.left + m_collider.right) / 2;
		m_fCenterPosY = (m_collider.top + m_collider.bottom) / 2;
	}

	switch (m_direct)
	{
	case MISSILEDIRECT_UP:
		SetRect(&m_collider, m_fPosX, m_fPosY, m_fPosX + 10, m_fPosY + 16);
		break;
	case MISSILEDIRECT_RIGHT:
		SetRect(&m_collider, m_fPosX, m_fPosY, m_fPosX + 16, m_fPosY + 10);
		break;
	case MISSILEDIRECT_LEFT:
		SetRect(&m_collider, m_fPosX, m_fPosY, m_fPosX + 16, m_fPosY + 10);
		break;
	case MISSILEDIRECT_DOWN:
		SetRect(&m_collider, m_fPosX, m_fPosY, m_fPosX + 10, m_fPosY + 16);
		break;
	default:
		break;
	}

	m_fCenterPosX = (m_collider.left + m_collider.right) / 2;
	m_fCenterPosY = (m_collider.top + m_collider.bottom) / 2;
}

bool Missile::IsInMap()
{
	if (m_collider.left >= 50 && m_collider.top >= 25 &&
		m_collider.right <= WINDOWWIDTH - 100 && m_collider.bottom <= WINDOWHEIGHT - 25)
	{
		return true;
	}

	return false;
}

MissileCollider Missile::GetCollider()
{
	MissileCollider MC;
	if (!m_bIsLive || m_bIsExplode)
	{
		MC.m_bIsHeroMissile = false;
		MC.m_collider = {0,0,0,0};
		return MC;
	}
	
	MC.m_collider = m_collider;
	MC.m_bIsHeroMissile = m_bIsHeroMissile;

	return MC;
}

bool Missile::GetIsLive()
{
	return m_bIsLive;
}

Missile::Missile()
{
	m_bIsLive = false;
}


Missile::~Missile()
{
}
