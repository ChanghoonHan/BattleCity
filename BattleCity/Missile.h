#pragma once
#include "BitMapManager.h"
#include "Scene.h"
#include "Block.h"
#include <vector>

struct TankCollider;

class GameScene;

#define MISSILESPEED 600

struct MissileCollider
{
	bool m_bIsHeroMissile;
	RECT m_collider;
};

enum MISSILEDIRECT
{
	MISSILEDIRECT_UP,
	MISSILEDIRECT_RIGHT,
	MISSILEDIRECT_LEFT,
	MISSILEDIRECT_DOWN,
};

class Missile
{
	static BitMapManager* m_lpBitMapManager;
	static GameScene* m_lpGameScene;

	bool m_bIsLive;
	bool m_bIsExplode;
	bool m_bIsHeroMissile;
	float m_fAfterExplodeTime;

	float m_fPosX;
	float m_fPosY;

	float m_fCenterPosX;
	float m_fCenterPosY;

	MISSILEDIRECT m_direct;
	RECT m_collider;
	
	bool IsInMap();
	void SetCollider();

public:
	void init();
	static void SetBitMapManager(BitMapManager* lpBitMapManager, GameScene* lpGameScene);
	bool fire(float fPosX, float fPosY, MISSILEDIRECT direct, bool isHeroMissile);
	void CheckCollWithObj();
	void Update(float fElapseTime);
	bool GetIsLive();
	void Draw(HDC& hdc);
	MissileCollider GetCollider();

	Missile();
	virtual ~Missile();
};

