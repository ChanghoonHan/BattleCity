#pragma once
#include "Tank.h"

class EnemyTank :
	public Tank
{
	bool m_bIsPowerUp;
	float m_fStackTimeForChangeDirect;
	float m_fStackTimeForChangeDirect2;
	MYKEYVAL m_key;
	int m_fOldTankPosX;
	int m_fOldTankPosY;
	virtual void SetCollider();

public:
	virtual void Init();
	virtual void Update(float fElapsedTime);
	virtual void Draw(HDC hdc);

	EnemyTank();
	virtual ~EnemyTank();
};

