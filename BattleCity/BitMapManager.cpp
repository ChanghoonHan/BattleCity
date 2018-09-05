#include "BitMapManager.h"

void BitMapManager::Draw(HDC& hdc, BLOCK block, int x, int y, int width, int height,
	int rendX, int rendY, int rendWidth, int rendHeight)
{
	m_blockBitMap[block].Draw(hdc, x, y, width, height, rendX, rendY, rendWidth, rendHeight);
}

void BitMapManager::Draw(HDC& hdc, UNIT unit, int x, int y, int width, int height)
{
	m_unitBitMap[unit].Draw(hdc, x, y, width, height);
}

void BitMapManager::Draw(HDC& hdc, EFFECT effect, int x, int y, int width, int height)
{
	m_effectBitMap[effect].Draw(hdc, x, y, width, height);
}

void BitMapManager::Draw(HDC& hdc, ICON icon, int x, int y, int width, int height)
{
	m_iconBitMap[icon].Draw(hdc, x, y, width, height);
}

void BitMapManager::Draw(HDC& hdc, BACK back, int x, int y, int width, int height)
{
	if (back != BACK_GAME)
	{
		m_backBitMap[back].Draw(hdc, x, y, width, height);
		return;
	}
	
	m_gameBackBitMap.Draw(hdc);
}

void BitMapManager::InitBitMapManager(HDC& hdc)
{
	m_gameBackBitMap.Init(hdc);

	m_backBitMap[BACK_BLACKBASE].Init(hdc, "blackBack.bmp");
	m_backBitMap[BACK_INTRO].Init(hdc, "intro.bmp");
	m_backBitMap[BACK_SETSTAGE].Init(hdc, "SetStageBack.bmp");
	m_backBitMap[BACK_GAMEOVER].Init(hdc, "endBack.bmp");

	m_blockBitMap[BLOCK_BRICK].Init(hdc, "block00.bmp");
	m_blockBitMap[BLOCK_WBRICK].Init(hdc, "block01.bmp");
	m_blockBitMap[BLOCK_WATER].Init(hdc, "block02.bmp");
	m_blockBitMap[BLOCK_TREE].Init(hdc, "block03.bmp");
	m_blockBitMap[BLOCK_ICE].Init(hdc, "block04.bmp");

	m_unitBitMap[UNIT_BOSS].Init(hdc, "block13.bmp");
	m_unitBitMap[UNIT_BOSSDIE].Init(hdc, "block14.bmp");

	m_unitBitMap[UNIT_HEROUP1].Init(hdc, "tank_up_00.bmp");
	m_unitBitMap[UNIT_HEROUP2].Init(hdc, "tank_up_01.bmp");
	m_unitBitMap[UNIT_HERORIGHT1].Init(hdc, "tank_right_00.bmp");
	m_unitBitMap[UNIT_HERORIGHT2].Init(hdc, "tank_right_01.bmp");
	m_unitBitMap[UNIT_HERODOWN1].Init(hdc, "tank_down_00.bmp");
	m_unitBitMap[UNIT_HERODOWN2].Init(hdc, "tank_down_01.bmp");
	m_unitBitMap[UNIT_HEROLEFT1].Init(hdc, "tank_left_00.bmp");
	m_unitBitMap[UNIT_HEROLEFT2].Init(hdc, "tank_left_01.bmp");

	m_unitBitMap[UNIT_ENEMYUP1].Init(hdc, "e_up_00.bmp");
	m_unitBitMap[UNIT_ENEMYUP2].Init(hdc, "e_up_01.bmp");
	m_unitBitMap[UNIT_ENEMYUP3].Init(hdc, "e_up_02.bmp");
	m_unitBitMap[UNIT_ENEMYRIGHT1].Init(hdc, "e_right_00.bmp");
	m_unitBitMap[UNIT_ENEMYRIGHT2].Init(hdc, "e_right_01.bmp");
	m_unitBitMap[UNIT_ENEMYRIGHT3].Init(hdc, "e_right_02.bmp");
	m_unitBitMap[UNIT_ENEMYDOWN1].Init(hdc, "e_down_00.bmp");
	m_unitBitMap[UNIT_ENEMYDOWN2].Init(hdc, "e_down_01.bmp");
	m_unitBitMap[UNIT_ENEMYDOWN3].Init(hdc, "e_down_02.bmp");
	m_unitBitMap[UNIT_ENEMYLEFT1].Init(hdc, "e_left_00.bmp");
	m_unitBitMap[UNIT_ENEMYLEFT2].Init(hdc, "e_left_01.bmp");
	m_unitBitMap[UNIT_ENEMYLEFT3].Init(hdc, "e_left_02.bmp");

	m_unitBitMap[UNIT_MISSILEUP].Init(hdc, "missile_up.bmp");
	m_unitBitMap[UNIT_MISSILERIGHT].Init(hdc, "missile_right.bmp");
	m_unitBitMap[UNIT_MISSILEDOWN].Init(hdc, "missile_down.bmp");
	m_unitBitMap[UNIT_MISSILELEFT].Init(hdc, "missile_left.bmp");

	m_effectBitMap[EFFECT_EXPLOSION1].Init(hdc, "explosion_00.bmp");
	m_effectBitMap[EFFECT_EXPLOSION2].Init(hdc, "explosion_01.bmp");
	m_effectBitMap[EFFECT_EXPLOSION3].Init(hdc, "explosion_02.bmp");
	m_effectBitMap[EFFECT_EXPLOSION4].Init(hdc, "explosion_03.bmp");
	m_effectBitMap[EFFECT_EXPLOSION5].Init(hdc, "explosion_04.bmp");

	m_effectBitMap[EFFECT_SHIELD1].Init(hdc, "shield_00.bmp");
	m_effectBitMap[EFFECT_SHIELD2].Init(hdc, "shield_01.bmp");

	m_iconBitMap[ICON_STAGE].Init(hdc, "stage_icon.bmp");
	m_iconBitMap[ICON_HERO].Init(hdc, "player_icon.bmp");
	m_iconBitMap[ICON_ENEMY].Init(hdc, "enemy_icon.bmp");
}

void BitMapManager::Release()
{
	for (size_t i = 0; i < BACK_END; i++)
	{
		if (i == BACK_GAME)
		{
			continue;
		}
		m_backBitMap[i].Release();
	}

	for (size_t i = 0; i < BLOCK_END; i++)
	{
		m_blockBitMap[i].Release();
	}

	for (size_t i = 0; i < UNIT_END; i++)
	{
		m_unitBitMap[i].Release();
	}

	for (size_t i = 0; i < EFFECT_END; i++)
	{
		m_effectBitMap[i].Release();
	}

	for (size_t i = 0; i < ICON_END; i++)
	{
		m_iconBitMap[i].Release();
	}
}

BitMapManager::BitMapManager()
{
}


BitMapManager::~BitMapManager()
{
}
