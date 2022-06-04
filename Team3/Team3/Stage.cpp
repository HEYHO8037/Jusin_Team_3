#include "stdafx.h"
#include "Stage.h"


CStage::CStage()
{
}


CStage::~CStage()
{
}

void CStage::Initialize(void)
{
}

void CStage::Update(void)
{
}

void CStage::LateUpdate(void)
{
}

void CStage::Render(HDC hDC)
{
	BitBlt(hDC, 0, 0, WINCX, WINCY, m_hMemDC, 0, 0, SRCCOPY);
}

void CStage::Release(void)
{
}
