#include "Tank.h"
#include "GameScene.h"

BitMapManager* Tank::m_lpBitMapManager = NULL;
GameScene* Tank::m_lpGameScene = NULL;

void Tank::Draw(HDC hdc)
{
	if (m_bIsExplode)
	{
		if (m_fExplodeBitMapChangeTime < 0.15)
		{
			m_lpBitMapManager->Draw(hdc, EFFECT_EXPLOSION4, (int)(m_fTankPosX - 25), (int)(m_fTankPosY - 25), 90, 90);
		}
		else if (m_fExplodeBitMapChangeTime < 0.3)
		{
			m_lpBitMapManager->Draw(hdc, EFFECT_EXPLOSION5, (int)(m_fTankPosX - 30), (int)(m_fTankPosY - 30), 100, 100);
		}
		else if (m_fExplodeBitMapChangeTime < 0.45 && !m_bIsHero)
		{
			TextOut(hdc, m_fTankPosX, m_fTankPosY, "100", strlen("100"));
		}
		else
		{
			m_bIsLive = false;
		}
	}
}

void Tank::SetBitMapMangerAndGameScene(BitMapManager* lpBitMapManager, GameScene* lpGameScene)
{
	m_lpBitMapManager = lpBitMapManager;
	m_lpGameScene = lpGameScene;
}

bool Tank::IsInMap()
{
	if (m_collider.left >= 50 && m_collider.top >= 25 &&
		m_collider.right <= WINDOWWIDTH - 100 && m_collider.bottom <= WINDOWHEIGHT - 25)
	{
		return true;
	}

	return false;
}

void Tank::Move(float fElapsedTime)
{
	if (!m_bIsMove || m_bIsExplode)
	{
		return;
	}

	switch (m_curDirect)
	{
	case DIRECT_UP:
		m_fTankPosY = m_fTankPosY - (m_iTankSpeed * fElapsedTime);
		SetCollider();

		if (!IsInMap() || m_lpGameScene->CheckCollWithBlock(GetTankCollider()) || m_lpGameScene->CheckCollWithTank(GetTankCollider(), m_curDirect))
		{
			m_fTankPosY = m_fTankPosY + (m_iTankSpeed * fElapsedTime);
			SetCollider();
		}

		if (m_lpGameScene->CheckCollWithIceBlock(GetTankCollider()))
		{
			m_fTankPosY = m_fTankPosY - (m_iTankSpeed * fElapsedTime);
			SetCollider();
			if (!IsInMap() || m_lpGameScene->CheckCollWithBlock(GetTankCollider()) || m_lpGameScene->CheckCollWithTank(GetTankCollider(), m_curDirect))
			{
				m_fTankPosY = m_fTankPosY + (m_iTankSpeed * fElapsedTime);
				SetCollider();
			}
		}

		break;

	case DIRECT_RIGHT:
		m_fTankPosX = m_fTankPosX + (m_iTankSpeed * fElapsedTime);
		SetCollider();

		if (!IsInMap() || m_lpGameScene->CheckCollWithBlock(GetTankCollider()) || m_lpGameScene->CheckCollWithTank(GetTankCollider(), m_curDirect))
		{
			m_fTankPosX = m_fTankPosX - (m_iTankSpeed * fElapsedTime);
		}

		if (m_lpGameScene->CheckCollWithIceBlock(GetTankCollider()))
		{
			m_fTankPosX = m_fTankPosX + (m_iTankSpeed * fElapsedTime);
			SetCollider();
			if (!IsInMap() || m_lpGameScene->CheckCollWithBlock(GetTankCollider()) || m_lpGameScene->CheckCollWithTank(GetTankCollider(), m_curDirect))
			{
				m_fTankPosX = m_fTankPosX - (m_iTankSpeed * fElapsedTime);
				SetCollider();
			}
		}

		break;

	case DIRECT_DOWN:
		m_fTankPosY = m_fTankPosY + (m_iTankSpeed * fElapsedTime);
		SetCollider();

		if (!IsInMap() || m_lpGameScene->CheckCollWithBlock(GetTankCollider()) || m_lpGameScene->CheckCollWithTank(GetTankCollider(), m_curDirect))
		{
			m_fTankPosY = m_fTankPosY - (m_iTankSpeed * fElapsedTime);
		}

		if (m_lpGameScene->CheckCollWithIceBlock(GetTankCollider()))
		{
			m_fTankPosY = m_fTankPosY + (m_iTankSpeed * fElapsedTime);
			SetCollider();
			if (!IsInMap() || m_lpGameScene->CheckCollWithBlock(GetTankCollider()) || m_lpGameScene->CheckCollWithTank(GetTankCollider(), m_curDirect))
			{
				m_fTankPosY = m_fTankPosY - (m_iTankSpeed * fElapsedTime);
				SetCollider();
			}
		}

		break;

	case DIRECT_LEFT:
		m_fTankPosX = m_fTankPosX - (m_iTankSpeed * fElapsedTime);
		SetCollider();

		if (!IsInMap() || m_lpGameScene->CheckCollWithBlock(GetTankCollider()) || m_lpGameScene->CheckCollWithTank(GetTankCollider(), m_curDirect))
		{
			m_fTankPosX = m_fTankPosX + (m_iTankSpeed * fElapsedTime);
		}

		if (m_lpGameScene->CheckCollWithIceBlock(GetTankCollider()))
		{
			m_fTankPosX = m_fTankPosX - (m_iTankSpeed * fElapsedTime);
			SetCollider();
			if (!IsInMap() || m_lpGameScene->CheckCollWithBlock(GetTankCollider()) || m_lpGameScene->CheckCollWithTank(GetTankCollider(), m_curDirect))
			{
				m_fTankPosX = m_fTankPosX + (m_iTankSpeed * fElapsedTime);
				SetCollider();
			}
		}

		break;

	default:
		break;
	}

	m_bIsMove = false;
}

void Tank::Init()
{
	m_bIsFirstTankBitMap = true;
	m_fTankBitMapChangeTime = 0;
	m_fExplodeBitMapChangeTime = 0;
	m_curDirect = DIRECT_UP;
	m_bIsExplode = false;
	m_bIsHero = false;
	m_fTankPosX = 0;
	m_fTankPosY = 0;
	m_fLiveTime = 0;
	m_fReLoadTime = 0;
	m_bIsLive = false;
	m_bIsMove = false;
	m_iMissileIdx = 0;
	for (size_t i = 0; i < MAXFIREMISSILE; i++)
	{
		m_lpMissile[i] = NULL;
	}
}

bool Tank::Instantiate(float fPosX, float fPosY)
{
	if (m_bIsLive)
	{
		return false;
	}
	m_fTankPosX = fPosX;
	m_fTankPosY = fPosY;
	m_bIsLive = true;
	m_bIsMove = false;
	SetCollider();
	return true;
}

bool Tank::IsLive()
{
	return m_bIsLive;
}

void Tank::OperatorInput(MYKEYVAL key)
{
	if (!m_bIsLive || m_bIsExplode)
	{
		return;
	}

	m_bIsMove = true;

	switch (key)
	{
	case MYKEYVAL_UP:
		m_curDirect = DIRECT_UP;
		break;
	case MYKEYVAL_DOWN:
		m_curDirect = DIRECT_DOWN;
		break;
	case MYKEYVAL_LEFT:
		m_curDirect = DIRECT_LEFT;
		break;
	case MYKEYVAL_RIGHT:
		m_curDirect = DIRECT_RIGHT;
		break;
	case MYKEYVAL_SPACE:
		m_bIsMove = false;
		if (m_fLiveTime > 1)
		{
			FireMissile();
		}
		break;
	case MYKEYVAL_NULL:
		break;
	default:
		break;
	}
}

void Tank::Update(float fElapsedTime)
{
	if (!m_bIsLive || m_bIsExplode)
	{
		m_fExplodeBitMapChangeTime += fElapsedTime;
		return;
	}

	if (!m_bCanFire)
	{
		m_fReLoadTime += fElapsedTime;
		if (m_fReLoadTime > m_fMaxReLoadTime)
		{
			m_fReLoadTime = 0;
			m_bCanFire = true;
		}
	}

	m_fLiveTime += fElapsedTime;
	m_fTankBitMapChangeTime += fElapsedTime;

	if (m_bIsMove && m_fLiveTime > 1)
	{
		if (m_fTankBitMapChangeTime > 0.1)
		{
			m_fTankBitMapChangeTime = 0;
			m_bIsFirstTankBitMap = !m_bIsFirstTankBitMap;
		}
		Move(fElapsedTime);
	}
	else
	{
		m_bIsMove = false;
	}
}

void Tank::FireMissile()
{
	if (!m_bCanFire)
	{
		return;
	}

	m_iMissileIdx = MAXFIREMISSILE;
	for (size_t i = 0; i < MAXFIREMISSILE; i++)
	{
		if (m_lpMissile[i] == NULL)
		{
			m_iMissileIdx = i;
			continue;
		}

		if (!m_lpMissile[i]->GetIsLive())
		{
			m_lpMissile[i] = NULL;
			m_iMissileIdx = i;
		}
	}

	if (m_iMissileIdx == MAXFIREMISSILE)
	{
		return;
	}

	switch (m_curDirect)
	{
	case DIRECT_UP:
		m_lpMissile[m_iMissileIdx] = m_lpGameScene->FireMissile(m_fTankPosX + 15, m_fTankPosY,
			MISSILEDIRECT_UP, m_bIsHero);
		break;
	case DIRECT_RIGHT:
		m_lpMissile[m_iMissileIdx] = m_lpGameScene->FireMissile(m_fTankPosX + 23, m_fTankPosY + 15,
			MISSILEDIRECT_RIGHT, m_bIsHero);
		break;
	case DIRECT_DOWN:
		m_lpMissile[m_iMissileIdx] = m_lpGameScene->FireMissile(m_fTankPosX + 15,m_fTankPosY + 23, 
			MISSILEDIRECT_DOWN, m_bIsHero);
		break;
	case DIRECT_LEFT:
		m_lpMissile[m_iMissileIdx] = m_lpGameScene->FireMissile(m_fTankPosX, m_fTankPosY + 15,
			MISSILEDIRECT_LEFT, m_bIsHero);
		break;
	case DIRECT_NULL:
		break;
	default:
		break;
	}

	if (m_lpMissile[m_iMissileIdx] != NULL)
	{
		m_bCanFire = false;
	}
}

TankCollider Tank::GetTankCollider()
{
	TankCollider TC;

	if (m_bIsLive)
	{
		TC.m_isHero = m_bIsHero;
		TC.m_collider = m_collider;
		return TC;
	}

	RECT rect;
	TC.m_isHero = m_bIsHero;
	TC.m_collider = { 0,0,0,0 };
	return TC;
}

void Tank::CheckCollisionWithMissile()
{
	if (m_bIsExplode)
	{
		return;
	}

	m_bIsExplode = m_lpGameScene->CheckCollWithMissile(GetTankCollider());
}

Tank::Tank()
{
}

Tank::~Tank()
{
}
