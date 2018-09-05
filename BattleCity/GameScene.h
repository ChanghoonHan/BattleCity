#pragma once
#include "Scene.h"
#include "Tank.h"
#include "Block.h"
#include "HeroTank.h"
#include "EnemyTank.h"
#include "Boss.h"
#include <vector>

#define MAPSIZE 26
#define MAXENEMY 6
#define MAXMISSILE 20

enum GAMESTATE
{
	GAMESTATE_NORMAL,
	GAMESTATE_GAMEOVER,
	GAMESTATE_GAMECLEAR
};

class GameScene :
	public Scene
{
	int m_iEnemyCount;
	int m_iHeroLife;
	GAMESTATE m_gameState;

	float m_fGameSceneEndWaitTime;
	bool m_bCanInstantiate;
	float m_fInstantiateBetweenTime;

	float m_fGameOverTextPosY;
	const int m_iInstantiateDirect[3][2] = { {60, 30}, {350, 30}, {640, 30} };

	Boss m_boss;
	HeroTank m_heroTank;
	EnemyTank m_enemyTank[MAXENEMY];
	Missile m_missile[MAXMISSILE];
	int m_iMissileCount;

	int m_mapCount;
	BLOCK m_mapMatrix[MAPSIZE][MAPSIZE];
	Block m_map[MAPSIZE*MAPSIZE];

	vector<BlockCollider> m_mapColliderList;
	vector<MissileCollider> m_missileColliderList;
	vector<TankCollider> m_tankColliderList;

	void InitMapMatrix();
	void SetMap();
	void DrawMap(HDC& hdc, bool bDrawTree);
	void SetMapColliderList();
	void SetMissileColliderList();
	void SetTanckColliderList();

public:
	bool CheckCollWithTank(TankCollider& tankCollider, DIRECT& tankDirect);
	bool CheckCollWithIceBlock(TankCollider& tankCollider);
	bool CheckCollWithBlock(TankCollider& tankCollider);
	bool CheckCollWithMissile(TankCollider& tankCollider);
	bool CheckCollWithTank(MissileCollider& missileCollider);
	bool CheckCollWithBlock(MissileCollider& missileCollider);
	bool CheckCollWithMissile(MissileCollider& missileCollider);

	Missile* FireMissile(float fPosX, float fPosY, MISSILEDIRECT direct, bool isHeroMissile);
	
	virtual void FirstInitScene(HDC& hdc);
	virtual void InitScene();
	virtual void OperatorInput(MYKEYVAL key);
	virtual void Update(float fElapsedTime);
	virtual SCENENUM Draw(HDC& hdc);

	GameScene();
	virtual ~GameScene();
};

