#pragma once
#include "BitMapManager.h"

struct BlockCollider
{
	BLOCK m_block;
	RECT m_collider;
};

class Block
{
	static BitMapManager* m_lpBitMapManager;

	float m_PosX;
	float m_PosY;
	int m_drowWidth;
	int m_drowHeight;
	int m_renderPosX;
	int m_renderPosY;
	int m_renderWidth;
	int m_renderHeight;
	BLOCK m_kindOfBlock;
	RECT m_collider;

public:
	static void SetBitMapManager(BitMapManager* lpBitMapManager);
	void MakeBlock(BLOCK kindOfBlock, float PosX, float PosY);
	void Draw(HDC hdc, bool bDrawTree);
	void CheckCollision(RECT collider);
	BLOCK GetKindOfBlock();
	BlockCollider GetCollider();

	Block();
	virtual ~Block();
};

