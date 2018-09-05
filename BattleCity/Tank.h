#pragma once
#include <Windows.h>
#include "Scene.h"
#include "BitMapManager.h"
#include <vector>

#define TANKSPEED 100
#define MAXFIREMISSILE 2

enum MYKEYVAL;
class GameScene;
class Missile;

enum TANKNUM
{
	TANKNUM_HERO,
	TANKNUM_1,
	TANKNUM_2,
	TANKNUM_3,
	TANKNUM_4,
	TANKNUM_5,
	TANKNUM_6,
};

struct TankCollider
{
	bool m_isHero;
	RECT m_collider;
};

enum DIRECT
{
	DIRECT_UP,
	DIRECT_RIGHT,
	DIRECT_DOWN,
	DIRECT_LEFT,
	DIRECT_NULL,
};

class Tank
{
protected:
	static BitMapManager* m_lpBitMapManager;
	static GameScene* m_lpGameScene;

	bool m_bIsFirstTankBitMap;
	bool m_bIsExplode;
	float m_fTankBitMapChangeTime;
	float m_fExplodeBitMapChangeTime;

	bool m_bCanFire;
	int m_iTankSpeed;
	float m_fReLoadTime;
	float m_fMaxReLoadTime;
	int m_iMissileIdx;
	Missile* m_lpMissile[MAXFIREMISSILE];

	DIRECT m_curDirect;
	float m_fTankPosX;
	float m_fTankPosY;
	float m_fLiveTime;
	RECT m_collider;
	bool m_bIsLive;
	bool m_bIsMove;
	bool m_bIsHero;

	virtual void Move(float fElapsedTime);
	virtual void SetCollider() = 0;
	bool IsInMap();

public:
	static void SetBitMapMangerAndGameScene (BitMapManager* lpBitMapManager, GameScene* m_lpGameScene);
	bool IsLive();
	bool Instantiate(float fPosX, float fPosY);
	void OperatorInput(MYKEYVAL key);

	TankCollider GetTankCollider();

	virtual void CheckCollisionWithMissile();
	virtual void FireMissile();
	virtual void Init();
	virtual void Update(float fElapsedTime);
	virtual void Draw(HDC hdc);

	Tank();
	virtual ~Tank();
};

