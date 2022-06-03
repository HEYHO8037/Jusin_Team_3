
#pragma once
#include "Include.h"

class CMyBmp_3
{
public:
	CMyBmp_3();
	~CMyBmp_3();

public:
	HDC Get_MemDC() { return m_hMemDC; }

public:
	void Load_Bmp(const TCHAR* pFilePath);
	void Release(void);

private:
	HDC m_hMemDC;

	HBITMAP m_hBitMap;
	HBITMAP m_hOldMap;

};

