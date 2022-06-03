#include "stdafx.h"
#include "MyBmp_3.h"


CMyBmp_3::CMyBmp_3()
{
}


CMyBmp_3::~CMyBmp_3()
{
	Release();
}

void CMyBmp_3::Load_Bmp(const TCHAR * pFilePath)
{
	HDC hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitMap = (HBITMAP)LoadImage(NULL,
		pFilePath,
		IMAGE_BITMAP,
		0, 0, //<-이미지 출력 시작점
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);


	m_hOldMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
	// 디씨에 그리고 비트맵 올드에 저장하고, 비트맵 씻고

}

void CMyBmp_3::Release(void)
{
	SelectObject(m_hMemDC, m_hOldMap);
	DeleteObject(m_hBitMap);
	DeleteDC(m_hMemDC);
}
