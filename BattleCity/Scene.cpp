#include "Scene.h"

BitMapManager* Scene::m_lpbitMapManager = NULL;
int Scene::m_iScore = 0;
int Scene::m_iHighScore = 20000;
int Scene::m_iStage = 0;
int Scene::m_iKilledEnemyCount = 0;

void Scene::SetBitMapManager(BitMapManager* lpbitMapManager)
{
	m_lpbitMapManager = lpbitMapManager;
}

Scene::Scene()
{
}

Scene::~Scene()
{
}