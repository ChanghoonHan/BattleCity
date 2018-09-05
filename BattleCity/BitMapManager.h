#pragma once
#include <Windows.h>
#include "BitMap.h"
#include "BackBitMap.h"

enum BLOCK
{
	BLOCK_BRICK,
	BLOCK_WBRICK,
	BLOCK_WATER,
	BLOCK_TREE,
	BLOCK_ICE,

	BLOCK_END,
};

enum UNIT
{
	UNIT_BOSS,
	UNIT_BOSSDIE,

	UNIT_HEROUP1,
	UNIT_HEROUP2,
	UNIT_HERORIGHT1,
	UNIT_HERORIGHT2,
	UNIT_HERODOWN1,
	UNIT_HERODOWN2,
	UNIT_HEROLEFT1,
	UNIT_HEROLEFT2,

	UNIT_ENEMYUP1,
	UNIT_ENEMYUP2,
	UNIT_ENEMYUP3,
	UNIT_ENEMYRIGHT1,
	UNIT_ENEMYRIGHT2,
	UNIT_ENEMYRIGHT3,
	UNIT_ENEMYDOWN1,
	UNIT_ENEMYDOWN2,
	UNIT_ENEMYDOWN3,
	UNIT_ENEMYLEFT1,
	UNIT_ENEMYLEFT2,
	UNIT_ENEMYLEFT3,

	UNIT_MISSILEUP,
	UNIT_MISSILERIGHT,
	UNIT_MISSILEDOWN,
	UNIT_MISSILELEFT,

	UNIT_END,
};

enum EFFECT
{
	EFFECT_EXPLOSION1,
	EFFECT_EXPLOSION2,
	EFFECT_EXPLOSION3,
	EFFECT_EXPLOSION4,
	EFFECT_EXPLOSION5,

	EFFECT_SHIELD1,
	EFFECT_SHIELD2,

	EFFECT_END,
};

enum ICON
{
	ICON_HERO,
	ICON_ENEMY,
	ICON_STAGE,

	ICON_END,
};

enum BACK
{
	BACK_BLACKBASE,
	BACK_INTRO,
	BACK_SETSTAGE,
	BACK_GAME,
	BACK_GAMEOVER,
	BACK_END,
};

class BitMapManager
{
	BackBitMap m_gameBackBitMap;
	BitMap m_backBitMap[BACK_END];
	BitMap m_blockBitMap[BLOCK_END];
	BitMap m_unitBitMap[UNIT_END];
	BitMap m_effectBitMap[EFFECT_END];
	BitMap m_iconBitMap[ICON_END];

public:
	void Draw(HDC& hdc, BLOCK block, int x, int y, int width = 0, int height = 0,
		int rendX = 0, int rendY = 0, int rendWidth = 0, int rendHeight = 0);
	void Draw(HDC& hdc, UNIT unit, int x, int y, int width = 0, int height = 0);
	void Draw(HDC& hdc, EFFECT effect, int x, int y, int width = 0, int height = 0);
	void Draw(HDC& hdc, ICON icon, int x, int y, int width = 0, int height = 0);
	void Draw(HDC& hdc, BACK back, int x, int y, int width = 0, int height = 0);

	void InitBitMapManager(HDC& hdc);
	void Release();

	BitMapManager();
	~BitMapManager();
};

