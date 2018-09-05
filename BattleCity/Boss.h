#pragma once
#include "BitMapManager.h"
#include "Missile.h"
#include <vector>

class Boss
{
	bool m_bIsLive;
	bool m_bIsExplode;
	RECT m_collider;
	float m_fElapsedTime;

	BitMapManager* m_lpBitMapManager;
	bool  CheckCollWithMissile(vector<MissileCollider> missileColliderList);
public:
	void Init(BitMapManager* lpBitMapManager);
	void Update(vector<MissileCollider> missileColliderList, float fElapsedTime);
	void Draw(HDC& hdc);
	RECT GetCollider();
	bool IsBossDie();


	Boss();
	~Boss();
};

