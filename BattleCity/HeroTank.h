#pragma once
#include "Tank.h"

class HeroTank :
	public Tank
{
	bool m_bOnShield;
	bool m_bIsFirstShieldBitMap;

	float m_fShieldBitMapChangeTime;
	
	virtual void SetCollider();

public:
	virtual void CheckCollisionWithMissile();
	virtual void Init();
	virtual void Update(float fElapsedTime);
	virtual void Draw(HDC hdc);
	HeroTank();
	virtual ~HeroTank();
};

