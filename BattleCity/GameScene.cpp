#include "GameScene.h"

void GameScene::FirstInitScene(HDC& hdc)
{
	Tank::SetBitMapMangerAndGameScene(m_lpbitMapManager, this);
	Missile::SetBitMapManager(m_lpbitMapManager, this);
	Block::SetBitMapManager(m_lpbitMapManager);
	m_boss.Init(m_lpbitMapManager);

	m_iMissileCount = 0;
	for (size_t i = 0; i < MAXMISSILE; i++)
	{
		m_missile[i].init();
	}

	m_heroTank.Init();
	for (size_t i = 0; i < MAXENEMY; i++)
	{
		m_enemyTank[i].Init();
	}
	
	m_fGameOverTextPosY = WINDOWHEIGHT;

	m_fGameSceneEndWaitTime = 0;
	m_gameState = GAMESTATE_NORMAL;
	m_bCanInstantiate = true;
	m_fInstantiateBetweenTime = 0;
	m_iEnemyCount = 20;
	m_iHeroLife = 3;

	InitMapMatrix();

	FILE* file = NULL;
	switch (m_iStage)
	{
	case 1:
		file = fopen("map1.txt", "r");
		fread(m_mapMatrix, sizeof(BLOCK), MAPSIZE*MAPSIZE, file);
		break;
	case 2:
		file = fopen("map2.txt", "r");
		fread(m_mapMatrix, sizeof(BLOCK), MAPSIZE*MAPSIZE, file);
		break;
	case 3:
		file = fopen("map3.txt", "r");
		fread(m_mapMatrix, sizeof(BLOCK), MAPSIZE*MAPSIZE, file);
		break;
	default:
		break;
	}
	SetMap();
	fclose(file);
	SetTanckColliderList();
	SetMapColliderList();
	SetMissileColliderList();
}

void GameScene::InitScene()
{
	m_boss.Init(m_lpbitMapManager);
	m_heroTank.Init();
	m_iMissileCount = 0;
	for (size_t i = 0; i < MAXMISSILE; i++)
	{
		m_missile[i].init();
	}

	for (size_t i = 0; i < MAXENEMY; i++)
	{
		m_enemyTank[i].Init();
	}
	m_fGameOverTextPosY = WINDOWHEIGHT;

	m_bCanInstantiate = true;
	m_fGameSceneEndWaitTime = 0;
	m_fInstantiateBetweenTime = 0;

	m_iEnemyCount = 20;
	m_iHeroLife = 3;

	m_heroTank.Instantiate(60 + (8 * 25), WINDOWHEIGHT - 70);
	m_enemyTank[0].Instantiate(60, 30);
	m_bCanInstantiate = false;
	m_gameState = GAMESTATE_NORMAL;

	m_iEnemyCount--;
	m_iHeroLife--;

	InitMapMatrix();
	FILE* file = NULL;
	switch (m_iStage)
	{
	case 1:
		file = fopen("map1.txt", "r");
		fread(m_mapMatrix, sizeof(BLOCK), MAPSIZE*MAPSIZE, file);
		break;
	case 2:
		file = fopen("map2.txt", "r");
		fread(m_mapMatrix, sizeof(BLOCK), MAPSIZE*MAPSIZE, file);
		break;
	case 3:
		file = fopen("map3.txt", "r");
		fread(m_mapMatrix, sizeof(BLOCK), MAPSIZE*MAPSIZE, file);
		break;
	default:
		break;
	}
	SetMap();

	fclose(file);
	SetTanckColliderList();
	SetMapColliderList();
	SetMissileColliderList();
}

void GameScene::OperatorInput(MYKEYVAL key)
{
	if (m_gameState == GAMESTATE_NORMAL)
	{
		m_heroTank.OperatorInput(key);
	}
}

void GameScene::Update(float fElapsedTime)
{
	m_iKilledEnemyCount = 20 - m_iEnemyCount;//»ý¼ºµÇÁö ¾ÊÀº Àû »©ÁÜ

	for (size_t i = 0; i < MAXENEMY; i++)//»ý¼ºµÇÀÖ°í »ì¾ÆÀÖ´Â Àû »©ÁÜ
	{
		if (m_enemyTank[i].IsLive())
		{
			m_iKilledEnemyCount--;
		}
	}

	if (m_gameState == GAMESTATE_GAMECLEAR)
	{
		m_fGameSceneEndWaitTime += (fElapsedTime *2);
	}

	if (m_gameState == GAMESTATE_GAMEOVER)
	{
		m_bCanInstantiate = false;
		m_fInstantiateBetweenTime = 0;

		m_fGameOverTextPosY -= (200 * fElapsedTime);
		if (m_fGameOverTextPosY < 330)
		{
			m_fGameOverTextPosY = 330;
			m_fGameSceneEndWaitTime += fElapsedTime;
		}
	}

	int randInstantiateDirectNum = rand() % 3;

	if (!m_heroTank.IsLive() && m_iHeroLife != 0)
	{
		m_heroTank.Init();
		m_heroTank.Instantiate(60 + (8 * 25), WINDOWHEIGHT - 70);
		m_iHeroLife--;
	}

	if (!m_bCanInstantiate)
	{
		m_fInstantiateBetweenTime += fElapsedTime;
		if (m_fInstantiateBetweenTime > 3)
		{
			m_bCanInstantiate = true;
		}
	}

	if (m_bCanInstantiate && m_iEnemyCount != 0)
	{
		for (size_t i = 0; i < MAXENEMY; i++)
		{
			if (!m_enemyTank[i].IsLive())
			{
				m_enemyTank[i].Init();
				m_enemyTank[i].Instantiate(m_iInstantiateDirect[randInstantiateDirectNum][0],
					m_iInstantiateDirect[randInstantiateDirectNum][1]);
				m_fInstantiateBetweenTime = 0;
				m_iEnemyCount--;
				m_bCanInstantiate = false;
				break;
			}
		}
	}

	m_heroTank.Update(fElapsedTime);

	for (size_t i = 0; i < MAXENEMY; i++)
	{
		m_enemyTank[i].Update(fElapsedTime);
	}

	for (size_t i = 0; i < MAXMISSILE; i++)
	{
		m_missile[i].Update(fElapsedTime);
	}

	SetMissileColliderList();
	SetTanckColliderList();
	SetMapColliderList();

	for (size_t i = 0; i < MAXENEMY; i++)
	{
		m_enemyTank[i].CheckCollisionWithMissile();
	}
	m_heroTank.CheckCollisionWithMissile();

	for (size_t i = 0; i < MAXMISSILE; i++)
	{
		m_missile[i].CheckCollWithObj();
	}
	for (size_t i = 0; i < m_mapCount; i++)
	{
		for (auto iter = m_missileColliderList.begin(); iter != m_missileColliderList.end(); iter++)
		{
			m_map[i].CheckCollision(iter->m_collider);	
		}
	}

	m_boss.Update(m_missileColliderList, fElapsedTime);

	if (m_iKilledEnemyCount == 20)
	{
		m_gameState = GAMESTATE_GAMECLEAR;
	}

	if ((!m_heroTank.IsLive() && m_iHeroLife == 0) || m_boss.IsBossDie())
	{
		m_gameState = GAMESTATE_GAMEOVER;
	}
}

SCENENUM GameScene::Draw(HDC& hdc)
{
	m_lpbitMapManager->Draw(hdc, BACK_GAME, 0, 0, WINDOWWIDTH, WINDOWHEIGHT);
	DrawMap(hdc, false);
	m_heroTank.Draw(hdc);
	for (size_t i = 0; i < MAXENEMY; i++)
	{
		m_enemyTank[i].Draw(hdc);
	}
	for (size_t i = 0; i < MAXMISSILE; i++)
	{
		m_missile[i].Draw(hdc);
	}
	DrawMap(hdc, true);
	m_boss.Draw(hdc);
	if (m_gameState == GAMESTATE_GAMEOVER)
	{
		SetTextColor(hdc, RGB(255, 0, 0));
		TextOut(hdc, 270, m_fGameOverTextPosY, "GAME OVER", strlen("GAME OVER"));
		SetTextColor(hdc, RGB(255, 255, 255));
	}

	if (m_fGameSceneEndWaitTime > 2)
	{
		return SCENENUM_GAMECLEAR;
	}
	return SCENENUM_GAME;
}

void GameScene::InitMapMatrix()
{
	memset(m_mapMatrix, BLOCK_END, MAPSIZE*MAPSIZE);
}

void GameScene::SetMap()
{
	m_mapCount = 0;

	for (size_t i = 0; i < MAPSIZE; i++)
	{
		for (size_t j = 0; j < MAPSIZE; j++)
		{
			if (m_mapMatrix[i][j] == BLOCK_END)
			{
				continue;
			}
			m_map[m_mapCount++].MakeBlock(m_mapMatrix[i][j], j, i);
		}
	}
}

void GameScene::DrawMap(HDC& hdc, bool bDrawTree)
{
	for (size_t i = 0; i < m_mapCount; i++)
	{
		m_map[i].Draw(hdc, bDrawTree);
	}

	m_lpbitMapManager->Draw(hdc, ICON_STAGE, WINDOWWIDTH - 75, WINDOWHEIGHT - 150, 50, 50);
	m_lpbitMapManager->Draw(hdc, ICON_HERO, WINDOWWIDTH - 80, WINDOWHEIGHT - 282, 25, 25);
	for (size_t i = 0; i < m_iEnemyCount; i++)
	{
		m_lpbitMapManager->Draw(hdc, ICON_ENEMY, WINDOWWIDTH - 75 + (i%2 * 25), 70 + (i / 2 * 25), 23, 23);
	}

	SetTextColor(hdc, RGB(255,255,255));
	char buf[8] = "";
	sprintf(buf, "%d", m_iStage);
	RECT rect = { WINDOWWIDTH - 75, WINDOWHEIGHT - 100, WINDOWWIDTH - 25, WINDOWHEIGHT - 60 };
	DrawText(hdc, buf, strlen(buf), &rect, DT_RIGHT);
	TextOut(hdc, WINDOWWIDTH - 75, WINDOWHEIGHT - 325, "1P", strlen("IP") );
	sprintf(buf, " %d", m_iHeroLife);
	TextOut(hdc, WINDOWWIDTH - 75, WINDOWHEIGHT - 295, buf, strlen(buf));
}

void GameScene::SetMapColliderList()
{
	m_mapColliderList.erase(m_mapColliderList.begin(), m_mapColliderList.end());

	for (size_t i = 0; i < m_mapCount; i++)
	{
		m_mapColliderList.push_back(m_map[i].GetCollider());
	}

	BlockCollider BC;
	BC.m_block = BLOCK_WBRICK;
	BC.m_collider = m_boss.GetCollider();
	m_mapColliderList.push_back(BC);
}

void GameScene::SetMissileColliderList()
{
	m_missileColliderList.erase(m_missileColliderList.begin(), m_missileColliderList.end());

	for (size_t i = 0; i < MAXMISSILE; i++)
	{
		if (!m_missile[i].GetIsLive())
		{
			continue;
		}
		m_missileColliderList.push_back(m_missile[i].GetCollider());
	}
}

void GameScene::SetTanckColliderList()
{
	m_tankColliderList.erase(m_tankColliderList.begin(), m_tankColliderList.end());

	for (size_t i = 0; i < MAXENEMY; i++)
	{
		m_tankColliderList.push_back(m_enemyTank[i].GetTankCollider());
	}

	m_tankColliderList.push_back(m_heroTank.GetTankCollider());
}

bool GameScene::CheckCollWithTank(TankCollider& tankCollider, DIRECT& tankDirect)
{
	RECT rect;

	for (auto iter = m_tankColliderList.begin(); iter != m_tankColliderList.end(); iter++)
	{
		if (IntersectRect(&rect, &tankCollider.m_collider, &iter->m_collider))
		{
			if ((rect.right - rect.left)*(rect.bottom - rect.top) < 900)
			{
				switch (tankDirect)
				{
				case DIRECT_UP:
					if (rect.top == tankCollider.m_collider.top)
					{
						return true;
					}
					break;
				case DIRECT_RIGHT:
					if (rect.right == tankCollider.m_collider.right)
					{
						return true;
					}
					break;
				case DIRECT_DOWN:
					if (rect.bottom == tankCollider.m_collider.bottom)
					{
						return true;
					}
					break;
				case DIRECT_LEFT:
					if (rect.left == tankCollider.m_collider.left)
					{
						return true;
					}
					break;
				case DIRECT_NULL:
					break;
				default:
					break;
				}
			}
		}
	}

	return false;
}

bool GameScene::CheckCollWithIceBlock(TankCollider& tankCollider)
{
	RECT rect;

	for (auto iter = m_mapColliderList.begin(); iter != m_mapColliderList.end(); iter++)
	{
		if (iter->m_block == BLOCK_ICE && IntersectRect(&rect, &tankCollider.m_collider, &iter->m_collider))
		{
			return true;
		}
	}

	return false;
}

bool GameScene::CheckCollWithBlock(TankCollider& tankCollider)
{
	RECT rect;

	for (auto iter = m_mapColliderList.begin(); iter != m_mapColliderList.end(); iter++)
	{
		if (iter->m_block == BLOCK_TREE || iter->m_block == BLOCK_ICE)
		{
			continue;
		}

		if (IntersectRect(&rect, &tankCollider.m_collider, &iter->m_collider))
		{
			return true;
		}
	}

	return false;
}

bool GameScene::CheckCollWithMissile(TankCollider& tankCollider)
{
	RECT rect;

	for (auto iter = m_missileColliderList.begin(); iter != m_missileColliderList.end(); iter++)
	{
		if (iter->m_bIsHeroMissile == tankCollider.m_isHero)
		{
			continue;
		}

		if (IntersectRect(&rect, &iter->m_collider, &tankCollider.m_collider))
		{
			return true;
		}
	}

	return false;
}

Missile* GameScene::FireMissile(float fPosX, float fPosY, MISSILEDIRECT direct, bool isHeroMissile)
{
	for (size_t i = 0; i < MAXMISSILE; i++)
	{
		if (m_missile[i].fire(fPosX, fPosY, direct, isHeroMissile))
		{
			return &m_missile[i];
		}
	}

	return NULL;
}

bool GameScene::CheckCollWithTank(MissileCollider& missileCollider)
{
	RECT rect;

	for (auto iter = m_tankColliderList.begin(); iter != m_tankColliderList.end(); iter++)
	{
		if (iter->m_isHero == missileCollider.m_bIsHeroMissile)
		{
			continue;
		}

		if (IntersectRect(&rect, &iter->m_collider, &missileCollider.m_collider))
		{
			return true;
		}
	}

	return false;
}

bool GameScene::CheckCollWithBlock(MissileCollider& missileCollider)
{
	RECT rect;

	for (auto iter = m_mapColliderList.begin(); iter != m_mapColliderList.end(); iter++)
	{
		if (iter->m_block == BLOCK_ICE || iter->m_block == BLOCK_TREE || iter->m_block == BLOCK_WATER)
		{
			continue;
		}

		if (IntersectRect(&rect, &iter->m_collider, &missileCollider.m_collider))
		{
			return true;
		}
	}

	return false;
}

bool GameScene::CheckCollWithMissile(MissileCollider& missileCollider)
{
	RECT rect;

	for (auto iter = m_missileColliderList.begin(); iter != m_missileColliderList.end(); iter++)
	{
		if (iter->m_bIsHeroMissile == missileCollider.m_bIsHeroMissile)
		{
			continue;
		}

		if (IntersectRect(&rect, &iter->m_collider, &missileCollider.m_collider))
		{
			return true;
		}
	}

	return false;
}

GameScene::GameScene()
{

}

GameScene::~GameScene()
{
}
