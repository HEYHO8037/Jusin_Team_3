#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"


CLine::CLine()
	: m_tInfo()
{
}


CLine::CLine(LINEPOINT& tLeft, LINEPOINT& tRight)
	: m_tInfo(tLeft, tRight)
{

}

CLine::CLine(LINE tLine)
	: m_tInfo(tLine)
{

}

CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HPEN hpen;
	HPEN hpenOld;

	hpen = CreatePen(PS_SOLID, 3, RGB(255, 140, 0));   
	hpenOld = (HPEN)::SelectObject(hDC, (HGDIOBJ)hpen);   
	MoveToEx(hDC, (int)m_tInfo.tLPoint.fX + iScrollX, (int)m_tInfo.tLPoint.fY + iScrollY, nullptr);
	LineTo(hDC, (int)m_tInfo.tRPoint.fX + iScrollX, (int)m_tInfo.tRPoint.fY + iScrollY);
	hpen = (HPEN)SelectObject(hDC, hpenOld);  
	DeleteObject(hpen);  

}
