#include "stdafx.h"
#include "Game_JUN.h"

#include "ObjMgr.h"
#include "AbstractFactory.h"

#include "Player_JUN.h"

#include "JUNLineMgr.h"

#include "Item_JUN.h"

#include "RandomMgr.h"


CGame_JUN::CGame_JUN()
{
}


CGame_JUN::~CGame_JUN()
{
}

void CGame_JUN::Initialize(void)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_JUN>::Create());
	m_dwItemTime = GetTickCount();
}

void CGame_JUN::Update(void)
{
	if (m_dwItemTime + 200 < GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem_JUN>::Create(CRandom::Random(0, 7)*45.f));
		m_dwItemTime = GetTickCount();
	}
	CJUNLineMgr::Get_Instance()->Update();

	CObjMgr::Get_Instance()->Update();
}

void CGame_JUN::LateUpdate(void)
{
	CJUNLineMgr::Get_Instance()->LateUpdate();
	CObjMgr::Get_Instance()->Late_Update();
}

void CGame_JUN::Render(HDC hDC)
{
	BitBlt(hDC, 0, 0, WINCX, WINCY, m_hMemDC, 0, 0, SRCCOPY);
	//Ellipse(hDC, 100, 0, 700, 600);
	CJUNLineMgr::Get_Instance()->Render(hDC);
	
	SelectObject(hDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hDC, RGB(0, 0, 0));
	Ellipse(hDC, 400 - 25, 300-25, 400+25, 300+25);
	SetDCBrushColor(hDC, RGB(255, 255, 255));

	CObjMgr::Get_Instance()->Render(hDC);
}

void CGame_JUN::Release(void)
{
	CObjMgr::Destroy_Instance();
}
