#include "BackBitMap.h"

void BackBitMap::Init(HDC& hdc)
{
	m_hdc = CreateCompatibleDC(hdc);
	m_NBitMap = CreateCompatibleBitmap(hdc, 800, 700);
	m_OBitMap = (HBITMAP)SelectObject(m_hdc, m_NBitMap);
	HBRUSH m_blackSolidBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH m_graySolidBrush = CreateSolidBrush(RGB(128, 128, 128));
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_hdc, m_graySolidBrush);
	Rectangle(m_hdc, 0, 0, 800, 700);
	SelectObject(m_hdc, m_blackSolidBrush);
	Rectangle(m_hdc, 50, 25, 700, 675);
	SelectObject(m_hdc, oldBrush);
	DeleteObject(m_blackSolidBrush);
	DeleteObject(m_graySolidBrush);
}

void BackBitMap::Draw(HDC& hdc)
{
	TransparentBlt(hdc, 0, 0, 800, 700, m_hdc, 0, 0, 800, 700, RGB(255, 0, 255));
}

BackBitMap::BackBitMap()
{
	
}


BackBitMap::~BackBitMap()
{
	SelectObject(m_hdc, m_OBitMap);
	DeleteObject(m_NBitMap);
	DeleteObject(m_hdc);
}
