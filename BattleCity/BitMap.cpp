#include "BitMap.h"

void BitMap::Init(HDC& hdc, string bitMapName)
{
	m_hdc = CreateCompatibleDC(hdc);
	m_NBitMap = (HBITMAP)LoadImage(NULL, bitMapName.c_str(), IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	BITMAP bmp_info;
	GetObject(m_NBitMap, sizeof(BITMAP), &bmp_info);
	m_imageHeight = bmp_info.bmHeight;
	m_imageWidth = bmp_info.bmWidth;

	m_OBitMap = (HBITMAP)SelectObject(m_hdc, m_NBitMap);
}

void BitMap::Draw(HDC& hdc, int x, int y, int width, int height, int rendX, int rendY, int rendWidth, int rendHeight)
{
	if (width == 0)
	{
		width = 25;
	}
	if (height == 0)
	{
		height = 25;
	}

	if (rendWidth == 0)
	{
		rendWidth = m_imageWidth;
	}

	if (rendHeight == 0)
	{
		rendHeight = m_imageHeight;
	}

	TransparentBlt(hdc, x, y, width, height,
		m_hdc, rendX, rendY, rendWidth, rendHeight, RGB(255, 0, 255));
}

void BitMap::Release()
{
	(HBITMAP)SelectObject(m_hdc, m_OBitMap);
	DeleteObject(m_NBitMap);
	DeleteDC(m_hdc);
	m_NBitMap = NULL;
}

BitMap::BitMap()
{
	m_NBitMap = NULL;
}

BitMap::~BitMap()
{
	Release();
}
