#include "Block.h"

BitMapManager* Block::m_lpBitMapManager = NULL;

void Block::SetBitMapManager(BitMapManager* lpBitMapManager)
{
	m_lpBitMapManager = lpBitMapManager;
}

void Block::MakeBlock(BLOCK kindOfBlock, float PosX, float PosY)
{
	m_kindOfBlock = kindOfBlock;
	m_PosX = (PosX * 25) + 50;
	m_PosY = (PosY * 25) + 25;
	m_drowWidth = 25;
	m_drowHeight = 25;
	SetRect(&m_collider, m_PosX, m_PosY, m_PosX + 25, m_PosY + 25);
	m_renderPosX = 0;
	m_renderPosY = 0;
	m_renderWidth = 17;
	m_renderHeight = 12;
}

void Block::Draw(HDC hdc, bool bDrawTree)
{
	if (bDrawTree)
	{
		if (m_kindOfBlock == BLOCK_TREE)
		{
			m_lpBitMapManager->Draw(hdc, m_kindOfBlock, m_PosX, m_PosY, m_drowWidth, m_drowHeight, m_renderPosX, m_renderPosY, m_renderWidth, m_renderHeight);
		}
		return;
	}

	m_lpBitMapManager->Draw(hdc, m_kindOfBlock, m_PosX, m_PosY, m_drowWidth, m_drowHeight, m_renderPosX, m_renderPosY, m_renderWidth, m_renderHeight);
}

void Block::CheckCollision(RECT collider)
{
	if (m_kindOfBlock != BLOCK_BRICK)
	{
		return;
	}

	RECT collRect;
	if (IntersectRect(&collRect, &collider, &m_collider))
	{
		if ((collider.bottom - collider.top) < (collider.right - collider.left))
		{
			if (collRect.left == m_collider.left)
			{
				SetRect(&m_collider, m_collider.left + 13, m_collider.top,
					m_collider.right, m_collider.bottom);
				m_PosX += 13;
				m_drowWidth -= 13;

				m_renderPosX += 9;
				m_renderWidth -= 9;

				if (m_renderWidth <= 0)
				{
					m_drowWidth = -1;
					m_renderWidth = -1;
					m_drowHeight = -1;
					m_renderHeight = -1;
					SetRect(&m_collider, 0, 0, 0, 0);
				}
			}

			if (collRect.right == m_collider.right)
			{
				SetRect(&m_collider, m_collider.left, m_collider.top,
					m_collider.right - 13, m_collider.bottom);

				m_drowWidth -= 13;

				m_renderWidth -= 9;

				if (m_renderWidth <= 0)
				{
					m_drowWidth = -1;
					m_renderWidth = -1;
					m_drowHeight = -1;
					m_renderHeight = -1;
					SetRect(&m_collider, 0, 0, 0, 0);
				}
			}
		}
		else
		{
			if (collRect.top == m_collider.top)
			{
				SetRect(&m_collider, m_collider.left, m_collider.top + 13,
					m_collider.right, m_collider.bottom);

				m_PosY += 13;
				m_drowHeight -= 13;

				m_renderPosY += 6;
				m_renderHeight -= 6;

				if (m_renderHeight <= 0)
				{
					m_drowWidth = -1;
					m_renderWidth = -1;
					m_drowHeight = -1;
					m_renderHeight = -1;
					SetRect(&m_collider, 0, 0, 0, 0);
				}
			}

			if (collRect.bottom == m_collider.bottom)
			{
				SetRect(&m_collider, m_collider.left, m_collider.top,
					m_collider.right, m_collider.bottom - 13);

				m_drowHeight -= 13;

				m_renderHeight -= 6;

				if (m_renderHeight <= 0)
				{
					m_drowWidth = -1;
					m_renderWidth = -1;
					m_drowHeight = -1;
					m_renderHeight = -1;
					SetRect(&m_collider, 0, 0, 0, 0);
				}
			}
		}
	}
}

BLOCK Block::GetKindOfBlock()
{
	return m_kindOfBlock;
}

BlockCollider Block::GetCollider()
{
	BlockCollider B;
	B.m_block = m_kindOfBlock;
	B.m_collider = m_collider;
	return B;
}

Block::Block()
{
}


Block::~Block()
{
}
