#pragma once
#include <Windows.h>

class BackBitMap
{
	HDC m_hdc;

	HBITMAP m_NBitMap;
	HBITMAP m_OBitMap;

public:
	void Init(HDC& hdc);
	void Draw(HDC& hdc);

	BackBitMap();
	~BackBitMap();
};

